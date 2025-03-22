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

def gameOfLife(self, board):
    """
    :type board: List[List[int]]
    :rtype: void Do not return anything, modify board in-place instead.
    """
    m = len(board)
    n = len(board[0]) if m else 0
    for i in xrange(m):
        for j in xrange(n):
            count = 0
            ## Count live cells in 3x3 block.
            for I in xrange(max(i-1, 0), min(i+2, m)):
                for J in xrange(max(j-1, 0), min(j+2, n)):
                    count += board[I][J] & 1

            # if (count == 4 && board[i][j]) means:
            #     Any live cell with three live neighbors lives.
            # if (count == 3) means:
            #     Any live cell with two live neighbors.
            #     Any dead cell with exactly three live neighbors lives.
            if (count == 4 and board[i][j]) or count == 3:
                board[i][j] |= 2  # Mark as live.

    for i in xrange(m):
        for j in xrange(n):
            board[i][j] >>= 1  # Update to the next state.



