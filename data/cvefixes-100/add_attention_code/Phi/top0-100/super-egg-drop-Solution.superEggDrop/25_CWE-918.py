def list_books():
    off = int(request.args.get("offset") or 0)
    limit = int(request.args.get("limit") or config.config_books_per_page)
    search = request.args.get("search")
    sort_param = request.args.get("sort", "id")
    order = request.args.get("order", "").lower()
    state = None
    join = tuple()

    if sort_param == "state":
        state = json.loads(request.args.get("state", "[]"))
    elif sort_param == "tags":
        order = [db.Tags.name.asc()] if order == "asc" else [db.Tags.name.desc()]
        join = db.books_tags_link, db.Books.id == db.books_tags_link.c.book, db.Tags
    elif sort_param == "series":
        order = [db.Series.name.asc()] if order == "asc" else [db.Series.name.desc()]
        join = db.books_series_link, db.Books.id == db.books_series_link.c.book, db.Series
    elif sort_param == "publishers":
        order = [db.Publishers.name.asc()] if order == "asc" else [db.Publishers.name.desc()]
        join = db.books_publishers_link, db.Books.id == db.books_publishers_link.c.book, db.Publishers
    elif sort_param == "authors":
        order = [db.Authors.name.asc(), db.Series.name, db.Books.series_index] if order == "asc" \
            else [db.Authors.name.desc(), db.Series.name.desc(), db.Books.series_index.desc()]
        join = db.books_authors_link, db.Books.id == db.books_authors_link.c.book, db.Authors, \
               db.books_series_link, db.Books.id == db.books_series_link.c.book, db.Series
    elif sort_param == "languages":
        order = [db.Languages.lang_code.asc()] if order == "asc" else [db.Languages.lang_code.desc()]
        join = db.books_languages_link, db.Books.id == db.books_languages_link.c.book, db.Languages
    elif order and sort_param in ["sort", "title", "authors_sort", "series_index"]:
        order = [text(sort_param + " " + order)]
    elif not state:
        order = [db.Books.timestamp.desc()]

    total_count = filtered_count = calibre_db.session.query(db.Books).filter(calibre_db.common_filters(allow_show_archived=True)).count()
    if state is not None:
        if search:
            books = calibre_db.search_query(search, config.config_read_column).all()
            filtered_count = len(books)
        else:
            if not config.config_read_column:
                books = (calibre_db.session.query(db.Books, ub.ReadBook.read_status, ub.ArchivedBook.is_archived)
                         .select_from(db.Books)
                         .outerjoin(ub.ReadBook,
                                    and_(ub.ReadBook.user_id == int(current_user.id),
                                         ub.ReadBook.book_id == db.Books.id)))
            else:
                read_column = ""
                try:
                    read_column = db.cc_classes[config.config_read_column]
                    books = (calibre_db.session.query(db.Books, read_column.value, ub.ArchivedBook.is_archived)
                             .select_from(db.Books)
                             .outerjoin(read_column, read_column.book == db.Books.id))
                except (KeyError, AttributeError):
                    log.error("Custom Column No.%d is not existing in calibre database", read_column)
                    # Skip linking read column and return None instead of read status
                    books = calibre_db.session.query(db.Books, None, ub.ArchivedBook.is_archived)
            books = (books.outerjoin(ub.ArchivedBook, and_(db.Books.id == ub.ArchivedBook.book_id,
                                                          int(current_user.id) == ub.ArchivedBook.user_id))
                     .filter(calibre_db.common_filters(allow_show_archived=True)).all())
        entries = calibre_db.get_checkbox_sorted(books, state, off, limit, order, True)
    elif search:
        entries, filtered_count, __ = calibre_db.get_search_results(search,
                                                                    off,
                                                                    [order,''],
                                                                    limit,
                                                                    True,
                                                                    config.config_read_column,
                                                                    *join)
    else:
        entries, __, __ = calibre_db.fill_indexpage_with_archived_books((int(off) / (int(limit)) + 1),
                                                                        db.Books,
                                                                        limit,
                                                                        True,
                                                                        order,
                                                                        True,
                                                                        True,
                                                                        config.config_read_column,
                                                                        *join)

    result = list()
    for entry in entries:
        val = entry[0]
        val.read_status = entry[1] == ub.ReadBook.STATUS_FINISHED
        val.is_archived = entry[2] is True
        for index in range(0, len(val.languages)):
            val.languages[index].language_name = isoLanguages.get_language_name(get_locale(), val.languages[
                index].lang_code)
        result.append(val)

    table_entries = {'totalNotFiltered': total_count, 'total': filtered_count, "rows": result}
    js_list = json.dumps(table_entries, cls=db.AlchemyEncoder)

    response = make_response(js_list)
    response.headers["Content-Type"] = "application/json; charset=utf-8"
    return response

def superEggDrop(self, K, N):
    """
    :type K: int
    :type N: int
    :rtype: int
    """
    def check(n, K, N):
        # let f(n, K) be the max number of floors could be solved by n moves and K eggs,
        # we want to do binary search to find min of n, s.t. f(n, K) >= N,
        # if we use one move to drop egg with X floors
        # 1. if it breaks, we can search new X in the range [X+1, X+f(n-1, K-1)]
        # 2. if it doesn't break, we can search new X in the range [X-f(n-1, K), X-1]
        # => f(n, K) = (X+f(n-1, K-1))-(X-f(n-1, K))+1 = f(n-1, K-1)+f(n-1, K)+1
        # => (1) f(n, K)   = f(n-1, K)  +1+f(n-1, K-1)
        #    (2) f(n, K-1) = f(n-1, K-1)+1+f(n-1, K-2)
        # let g(n, K) = f(n, K)-f(n, K-1), and we subtract (1) by (2)
        # => g(n, K) = g(n-1, K)+g(n-1, K-1), obviously, it is binomial coefficient
        # => C(n, K) = g(n, K) = f(n, K)-f(n, K-1),
        #    which also implies if we have one more egg with n moves and x-1 egges, we can have more C(n, x) floors solvable
        # => f(n, K) = C(n, K)+f(n, K-1) = C(n, K) + C(n, K-1) + ... + C(n, 1) + f(n, 0) = sum(C(n, k) for k in [1, K])
        # => all we have to do is to check sum(C(n, k) for k in [1, K]) >= N,
        #    if true, there must exist a 1-to-1 mapping from each F in [1, N] to each sucess and failure sequence of every C(n, k) combinations for k in [1, K]
        total, c = 0, 1
        for k in xrange(1, K+1):
            c *= n-k+1
            c //= k
            total += c
            if total >= N:
                return True
        return False

    left, right = 1, N
    while left <= right:
        mid = left + (right-left)//2
        if check(mid, K, N):
            right = mid-1
        else:
            left = mid+1
    return left



