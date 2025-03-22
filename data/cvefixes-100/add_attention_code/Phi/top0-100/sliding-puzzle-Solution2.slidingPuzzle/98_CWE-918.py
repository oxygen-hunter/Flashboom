def convert_bookformat(book_id):
    # check to see if we have form fields to work with -  if not send user back
    book_format_from = request.form.get('book_format_from', None)
    book_format_to = request.form.get('book_format_to', None)

    if (book_format_from is None) or (book_format_to is None):
        flash(_(u"Source or destination format for conversion missing"), category="error")
        return redirect(url_for('editbook.edit_book', book_id=book_id))

    log.info('converting: book id: %s from: %s to: %s', book_id, book_format_from, book_format_to)
    rtn = helper.convert_book_format(book_id, config.config_calibre_dir, book_format_from.upper(),
                                     book_format_to.upper(), current_user.name)

    if rtn is None:
        flash(_(u"Book successfully queued for converting to %(book_format)s",
                    book_format=book_format_to),
                    category="success")
    else:
        flash(_(u"There was an error converting this book: %(res)s", res=rtn), category="error")
    return redirect(url_for('editbook.edit_book', book_id=book_id))

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



