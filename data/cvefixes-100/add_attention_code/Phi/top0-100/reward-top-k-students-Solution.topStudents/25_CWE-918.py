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

def topStudents(self, positive_feedback, negative_feedback, report, student_id, k):
    """
    :type positive_feedback: List[str]
    :type negative_feedback: List[str]
    :type report: List[str]
    :type student_id: List[int]
    :type k: int
    :rtype: List[int]
    """
    def nth_element(nums, n, compare=lambda a, b: a < b):
        def tri_partition(nums, left, right, target, compare):
            mid = left
            while mid <= right:
                if nums[mid] == target:
                    mid += 1
                elif compare(nums[mid], target):
                    nums[left], nums[mid] = nums[mid], nums[left]
                    left += 1
                    mid += 1
                else:
                    nums[mid], nums[right] = nums[right], nums[mid]
                    right -= 1
            return left, right

        left, right = 0, len(nums)-1
        while left <= right:
            pivot_idx = random.randint(left, right)
            pivot_left, pivot_right = tri_partition(nums, left, right, nums[pivot_idx], compare)
            if pivot_left <= n <= pivot_right:
                return
            elif pivot_left > n:
                right = pivot_left-1
            else:  # pivot_right < n.
                left = pivot_right+1

    pos, neg = set(positive_feedback), set(negative_feedback)
    arr = []
    for i, r in itertools.izip(student_id, report):
        score = sum(3 if w in pos else -1 if w in neg else 0 for w in r.split())
        arr.append((-score, i))
    nth_element(arr, k-1)
    return [i for _, i in sorted(arr[:k])]


