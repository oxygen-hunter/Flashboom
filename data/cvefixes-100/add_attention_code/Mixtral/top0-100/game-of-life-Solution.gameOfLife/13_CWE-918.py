def author_list():
    if current_user.check_visibility(constants.SIDEBAR_AUTHOR):
        if current_user.get_view_property('author', 'dir') == 'desc':
            order = db.Authors.sort.desc()
            order_no = 0
        else:
            order = db.Authors.sort.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Authors, func.count('books_authors_link.book').label('count')) \
            .join(db.books_authors_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_authors_link.author')).order_by(order).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Authors.sort, 1, 1)).label('char')) \
            .join(db.books_authors_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Authors.sort, 1, 1))).all()
        # If not creating a copy, readonly databases can not display authornames with "|" in it as changing the name
        # starts a change session
        autor_copy = copy.deepcopy(entries)
        for entry in autor_copy:
            entry.Authors.name = entry.Authors.name.replace('|', ',')
        return render_title_template('list.html', entries=autor_copy, folder='web.books_list', charlist=charlist,
                                     title=u"Authors", page="authorlist", data='author', order=order_no)
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



