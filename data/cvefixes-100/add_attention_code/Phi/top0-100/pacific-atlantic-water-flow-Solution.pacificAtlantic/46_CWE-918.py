def render_downloaded_books(page, order, user_id):
    if current_user.role_admin():
        user_id = int(user_id)
    else:
        user_id = current_user.id
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD):
        if current_user.show_detail_random():
            random = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                .order_by(func.random()).limit(config.config_random_books)
        else:
            random = false()

        entries, __, pagination = calibre_db.fill_indexpage(page,
                                                            0,
                                                            db.Books,
                                                            ub.Downloads.user_id == user_id,
                                                            order[0],
                                                            False, 0,
                                                            db.books_series_link,
                                                            db.Books.id == db.books_series_link.c.book,
                                                            db.Series,
                                                            ub.Downloads, db.Books.id == ub.Downloads.book_id)
        for book in entries:
            if not calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                             .filter(db.Books.id == book.id).first():
                ub.delete_download(book.id)
        user = ub.session.query(ub.User).filter(ub.User.id == user_id).first()
        return render_title_template('index.html',
                                     random=random,
                                     entries=entries,
                                     pagination=pagination,
                                     id=user_id,
                                     title=_(u"Downloaded books by %(user)s",user=user.name),
                                     page="download",
                                     order=order[1])
    else:
        abort(404)

def pacificAtlantic(self, matrix):
    """
    :type matrix: List[List[int]]
    :rtype: List[List[int]]
    """
    PACIFIC, ATLANTIC = 1, 2

    def pacificAtlanticHelper(matrix, x, y, prev_height, prev_val, visited, res):
        if (not 0 <= x < len(matrix)) or \
           (not 0 <= y < len(matrix[0])) or \
           matrix[x][y] < prev_height or \
           (visited[x][y] | prev_val) == visited[x][y]:
            return

        visited[x][y] |= prev_val
        if visited[x][y] == (PACIFIC | ATLANTIC):
            res.append((x, y))

        for d in [(0, -1), (0, 1), (-1, 0), (1, 0)]:
            pacificAtlanticHelper(matrix, x + d[0], y + d[1], matrix[x][y], visited[x][y], visited, res)

    if not matrix:
        return []

    res = []
    m, n = len(matrix),len(matrix[0])
    visited = [[0 for _ in xrange(n)] for _ in xrange(m)]

    for i in xrange(m):
        pacificAtlanticHelper(matrix, i, 0, float("-inf"), PACIFIC, visited, res)
        pacificAtlanticHelper(matrix, i, n - 1, float("-inf"), ATLANTIC, visited, res)
    for j in xrange(n):
        pacificAtlanticHelper(matrix, 0, j, float("-inf"), PACIFIC, visited, res)
        pacificAtlanticHelper(matrix, m - 1, j, float("-inf"), ATLANTIC, visited, res)

    return res



