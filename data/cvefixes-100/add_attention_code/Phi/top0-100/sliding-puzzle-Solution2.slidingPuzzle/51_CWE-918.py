def render_read_books(page, are_read, as_xml=False, order=None):
    sort_param = order[0] if order else []
    if not config.config_read_column:
        if are_read:
            db_filter = and_(ub.ReadBook.user_id == int(current_user.id),
                             ub.ReadBook.read_status == ub.ReadBook.STATUS_FINISHED)
        else:
            db_filter = coalesce(ub.ReadBook.read_status, 0) != ub.ReadBook.STATUS_FINISHED
        entries, random, pagination = calibre_db.fill_indexpage(page, 0,
                                                                db.Books,
                                                                db_filter,
                                                                sort_param,
                                                                False, 0,
                                                                db.books_series_link,
                                                                db.Books.id == db.books_series_link.c.book,
                                                                db.Series,
                                                                ub.ReadBook, db.Books.id == ub.ReadBook.book_id)
    else:
        try:
            if are_read:
                db_filter = db.cc_classes[config.config_read_column].value == True
            else:
                db_filter = coalesce(db.cc_classes[config.config_read_column].value, False) != True
            entries, random, pagination = calibre_db.fill_indexpage(page, 0,
                                                                    db.Books,
                                                                    db_filter,
                                                                    sort_param,
                                                                    False, 0,
                                                                    db.books_series_link,
                                                                    db.Books.id == db.books_series_link.c.book,
                                                                    db.Series,
                                                                    db.cc_classes[config.config_read_column])
        except (KeyError, AttributeError):
            log.error("Custom Column No.%d is not existing in calibre database", config.config_read_column)
            if not as_xml:
                flash(_("Custom Column No.%(column)d is not existing in calibre database",
                        column=config.config_read_column),
                      category="error")
                return redirect(url_for("web.index"))
            return [] # ToDo: Handle error Case for opds

    if as_xml:
        return entries, pagination
    else:
        if are_read:
            name = _(u'Read Books') + ' (' + str(pagination.total_count) + ')'
            pagename = "read"
        else:
            name = _(u'Unread Books') + ' (' + str(pagination.total_count) + ')'
            pagename = "unread"
        return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                     title=name, page=pagename, order=order[1])

def slidingPuzzle(self, board):
    """
    :type board: List[List[int]]
    :rtype: int
    """
    def heuristic_estimate(board, R, C, expected):
        result = 0
        for i in xrange(R):
            for j in xrange(C):
                val = board[C*i + j]
                if val == 0: continue
                r, c = expected[val]
                result += abs(r-i) + abs(c-j)
        return result

    R, C = len(board), len(board[0])
    begin = tuple(itertools.chain(*board))
    end = tuple(range(1, R*C) + [0])
    end_wrong = tuple(range(1, R*C-2) + [R*C-1, R*C-2, 0])
    expected = {(C*i+j+1) % (R*C) : (i, j)
                for i in xrange(R) for j in xrange(C)}

    min_heap = [(0, 0, begin.index(0), begin)]
    lookup = {begin: 0}
    while min_heap:
        f, g, zero, board = heapq.heappop(min_heap)
        if board == end: return g
        if board == end_wrong: return -1
        if f > lookup[board]: continue

        r, c = divmod(zero, C)
        for direction in ((-1, 0), (1, 0), (0, -1), (0, 1)):
            i, j = r+direction[0], c+direction[1]
            if 0 <= i < R and 0 <= j < C:
                new_zero = C*i+j
                tmp = list(board)
                tmp[zero], tmp[new_zero] = tmp[new_zero], tmp[zero]
                new_board = tuple(tmp)
                f = g+1+heuristic_estimate(new_board, R, C, expected)
                if f < lookup.get(new_board, float("inf")):
                    lookup[new_board] = f
                    heapq.heappush(min_heap, (f, g+1, new_zero, new_board))
    return -1



