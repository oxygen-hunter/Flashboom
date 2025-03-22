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

def canMouseWin(self, grid, catJump, mouseJump):
    """
    :type grid: List[str]
    :type catJump: int
    :type mouseJump: int
    :rtype: bool
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    DRAW, MOUSE, CAT = range(3)
    def parents(m, c, t):
        if t == CAT:
            for nm in graph[m, MOUSE^CAT^t]:
                yield nm, c, MOUSE^CAT^t
        else:
            for nc in graph[c, MOUSE^CAT^t]:
                yield m, nc, MOUSE^CAT^t

    R, C = len(grid), len(grid[0])
    N = R*C
    WALLS = set()
    FOOD, MOUSE_START, CAT_START = [-1]*3
    for r in xrange(R):
        for c in xrange(C):
            if grid[r][c] == 'M':
                MOUSE_START = r*C + c
            elif grid[r][c] == 'C':
                CAT_START = r*C + c
            elif grid[r][c] == 'F':
                FOOD = r*C + c
            elif grid[r][c] == '#':
                WALLS.add(r*C + c)
    graph = collections.defaultdict(set)
    jump = {MOUSE:mouseJump, CAT:catJump}
    for r in xrange(R):
        for c in xrange(C):
            if grid[r][c] == '#':
                continue
            pos = r*C + c
            for t in [MOUSE, CAT]:
                for dr, dc in directions:
                    for d in xrange(jump[t]+1):
                        nr, nc = r+dr*d, c+dc*d
                        if not (0 <= nr < R and 0 <= nc < C and grid[nr][nc] != '#'):
                            break
                        graph[pos, t].add(nr*C + nc)

    degree = {}
    for m in xrange(N):
        for c in xrange(N):
            # degree[m, c, MOUSE] = len(graph[m, MOUSE])
            degree[m, c, CAT] = len(graph[c, CAT])
    color = collections.defaultdict(int)
    q1 = collections.deque()
    # q2 = collections.deque()
    for i in xrange(N):
        if i in WALLS or i == FOOD:
            continue
        color[FOOD, i, CAT] = MOUSE
        q1.append((FOOD, i, CAT))
        color[i, FOOD, MOUSE] = CAT
        # q2.append((i, FOOD, MOUSE))
        for t in [MOUSE, CAT]:
            color[i, i, t] = CAT
            # q2.append((i, i, t))
    while q1:
        i, j, t = q1.popleft()
        for ni, nj, nt in parents(i, j, t):
            if color[ni, nj, nt] != DRAW:
                continue
            if t == CAT:
                color[ni, nj, nt] = MOUSE
                q1.append((ni, nj, nt))
                continue
            degree[ni, nj, nt] -= 1
            if not degree[ni, nj, nt]:
                color[ni, nj, nt] = MOUSE
                q1.append((ni, nj, nt))
    # while q2:
    #     i, j, t = q2.popleft()
    #     for ni, nj, nt in parents(i, j, t):
    #         if color[ni, nj, nt] != DRAW:
    #             continue
    #         if t == MOUSE:
    #             color[ni, nj, nt] = CAT
    #             q2.append((ni, nj, nt))
    #             continue
    #         degree[ni, nj, nt] -= 1
    #         if not degree[ni, nj, nt]:
    #             color[ni, nj, nt] = CAT
    #             q2.append((ni, nj, nt))
    return color[MOUSE_START, CAT_START, MOUSE] == MOUSE


