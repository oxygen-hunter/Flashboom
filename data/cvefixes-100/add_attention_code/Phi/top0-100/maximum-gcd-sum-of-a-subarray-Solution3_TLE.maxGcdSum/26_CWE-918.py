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

def maxGcdSum(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    def gcd(a, b):
        while b:
            a, b = b, a%b
        return a

    def binary_search_right(left, right, check):
        while left <= right:
            mid = left + (right-left)//2
            if not check(mid):
                right = mid-1
            else:
                left = mid+1
        return right

    # RMQ - Sparse Table
    # Template: https://github.com/kamyu104/GoogleCodeJam-Farewell-Rounds/blob/main/Round%20D/genetic_sequences2.py3
    # Time:  ctor:  O(NlogN) * O(fn)
    #        query: O(fn)
    # Space: O(NlogN)
    class SparseTable(object):
        def __init__(self, arr, fn):
            self.fn = fn
            self.bit_length = [0]
            n = len(arr)
            k = n.bit_length()-1  # log2_floor(n)
            for i in xrange(k+1):
                self.bit_length.extend(i+1 for _ in xrange(min(1<<i, (n+1)-len(self.bit_length))))
            self.st = [[0]*n for _ in xrange(k+1)]
            self.st[0] = arr[:]
            for i in xrange(1, k+1):  # Time: O(NlogN) * O(fn)
                for j in xrange((n-(1<<i))+1):
                    self.st[i][j] = fn(self.st[i-1][j], self.st[i-1][j+(1<<(i-1))])
    
        def query(self, L, R):  # Time: O(fn)
            i = self.bit_length[R-L+1]-1  # log2_floor(R-L+1)
            return self.fn(self.st[i][L], self.st[i][R-(1<<i)+1])
    
    prefix = [0]*(len(nums)+1)
    for i, x in enumerate(nums):
        prefix[i+1] = prefix[i]+x
    result = 0
    rmq = SparseTable(nums, gcd)
    for left, x in enumerate(nums):
        right = left
        while right < len(nums):  # O(logr) times
            g = rmq.query(left, right)
            right = binary_search_right(right, len(nums)-1, lambda x: rmq.query(left, x) >= g)  # Time: O(logn) * O(logr)
            if right-left+1 >= k:
                result = max(result, (prefix[right+1]-prefix[left])*g)
            right += 1
    return result


