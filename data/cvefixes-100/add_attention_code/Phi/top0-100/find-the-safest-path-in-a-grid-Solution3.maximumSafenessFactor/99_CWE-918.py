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

def maximumSafenessFactor(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    DIRECTIONS = ((1, 0), (0, 1), (-1, 0), (0, -1))
    def bfs():
        dist = [[0 if grid[r][c] == 1 else -1 for c in xrange(len(grid[0]))] for r in xrange(len(grid))]
        q = [(r, c) for r in xrange(len(grid)) for c in xrange(len(grid[0])) if grid[r][c]]
        d = 0
        while q:
            new_q = []
            for r, c in q:
                for dr, dc in DIRECTIONS:
                    nr, nc = r+dr, c+dc
                    if not (0 <= nr < len(dist) and 0 <= nc < len(dist[0]) and dist[nr][nc] == -1):
                        continue
                    dist[nr][nc] = d+1
                    new_q.append((nr, nc))
            q = new_q
            d += 1
        return dist

    def check(x):
        lookup = [[False]*len(dist[0]) for _ in xrange(len(dist))]
        q = [(0, 0)]
        lookup[0][0] = True
        while q:
            new_q = []
            for r, c in q:
                for dr, dc in DIRECTIONS:
                    nr, nc = r+dr, c+dc
                    if not (0 <= nr < len(dist) and 0 <= nc < len(dist[0]) and dist[nr][nc] >= x and not lookup[nr][nc]):
                        continue
                    lookup[nr][nc] = True
                    new_q.append((nr, nc))
            q = new_q
        return lookup[-1][-1]

    dist = bfs()
    left, right = 0, dist[0][0]
    while left <= right:
        mid = left + (right-left)//2
        if not check(mid):
            right = mid-1
        else:
            left = mid+1
    return right


