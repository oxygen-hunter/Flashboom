def ratings_list():
    if current_user.check_visibility(constants.SIDEBAR_RATING):
        if current_user.get_view_property('ratings', 'dir') == 'desc':
            order = db.Ratings.rating.desc()
            order_no = 0
        else:
            order = db.Ratings.rating.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Ratings, func.count('books_ratings_link.book').label('count'),
                                   (db.Ratings.rating / 2).label('name')) \
            .join(db.books_ratings_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_ratings_link.rating')).order_by(order).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=list(),
                                     title=_(u"Ratings list"), page="ratingslist", data="ratings", order=order_no)
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



