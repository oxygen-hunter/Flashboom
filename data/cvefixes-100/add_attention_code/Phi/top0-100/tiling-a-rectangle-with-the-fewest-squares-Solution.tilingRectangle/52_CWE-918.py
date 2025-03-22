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

def tilingRectangle(self, n, m):
    """
    :type n: int
    :type m: int
    :rtype: int
    """
    def find_next(board):
        for i in xrange(len(board)):
            for j in xrange(len(board[0])):
                if not board[i][j]:
                    return i, j
        return -1, -1

    def find_max_length(board, i, j):
        max_length = 1
        while i+max_length-1 < len(board) and \
              j+max_length-1 < len(board[0]):
            for r in xrange(i, i+max_length-1):
                if board[r][j+max_length-1]:
                    return max_length-1
            for c in xrange(j, j+max_length):
                if board[i+max_length-1][c]:
                    return max_length-1
            max_length += 1
        return max_length-1

    def fill(board, i, j, length, val):
        for r in xrange(i, i+length):
            for c in xrange(j, j+length):
                board[r][c] = val

    def backtracking(board, count, result):
        if count >= result[0]:  # pruning
            return
        i, j = find_next(board)
        if (i, j) == (-1, -1):  # finished
            result[0] = min(result[0], count)
            return
        max_length = find_max_length(board, i, j)
        for k in reversed(xrange(1, max_length+1)):
            fill(board, i, j, k, 1)
            backtracking(board, count+1, result)
            fill(board, i, j, k, 0)

    if m > n:
        return self.tilingRectangle(m, n)
    board = [[0]*m for _ in xrange(n)]
    result = [float("inf")]
    backtracking(board, 0, result)
    return result[0]


