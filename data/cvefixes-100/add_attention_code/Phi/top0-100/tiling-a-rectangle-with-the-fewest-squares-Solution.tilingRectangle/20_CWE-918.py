def download_list():
    if current_user.get_view_property('download', 'dir') == 'desc':
        order = ub.User.name.desc()
        order_no = 0
    else:
        order = ub.User.name.asc()
        order_no = 1
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD) and current_user.role_admin():
        entries = ub.session.query(ub.User, func.count(ub.Downloads.book_id).label('count'))\
            .join(ub.Downloads).group_by(ub.Downloads.user_id).order_by(order).all()
        charlist = ub.session.query(func.upper(func.substr(ub.User.name, 1, 1)).label('char')) \
            .filter(ub.User.role.op('&')(constants.ROLE_ANONYMOUS) != constants.ROLE_ANONYMOUS) \
            .group_by(func.upper(func.substr(ub.User.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Downloads"), page="downloadlist", data="download", order=order_no)
    else:
        abort(404)

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


