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



