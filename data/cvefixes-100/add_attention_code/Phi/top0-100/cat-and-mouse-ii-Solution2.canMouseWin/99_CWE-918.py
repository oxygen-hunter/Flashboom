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

def canMouseWin(self, grid, catJump, mouseJump):
    """
    :type grid: List[str]
    :type catJump: int
    :type mouseJump: int
    :rtype: bool
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    DRAW, MOUSE, CAT = range(3)
    def parents(m, c, t):
        if t == CAT:
            for nm in graph[m, MOUSE^CAT^t]:
                yield nm, c, MOUSE^CAT^t
        else:
            for nc in graph[c, MOUSE^CAT^t]:
                yield m, nc, MOUSE^CAT^t

    R, C = len(grid), len(grid[0])
    N = R*C
    WALLS = set()
    FOOD, MOUSE_START, CAT_START = [-1]*3
    for r in xrange(R):
        for c in xrange(C):
            if grid[r][c] == 'M':
                MOUSE_START = r*C + c
            elif grid[r][c] == 'C':
                CAT_START = r*C + c
            elif grid[r][c] == 'F':
                FOOD = r*C + c
            elif grid[r][c] == '#':
                WALLS.add(r*C + c)
    graph = collections.defaultdict(set)
    jump = {MOUSE:mouseJump, CAT:catJump}
    for r in xrange(R):
        for c in xrange(C):
            if grid[r][c] == '#':
                continue
            pos = r*C + c
            for t in [MOUSE, CAT]:
                for dr, dc in directions:
                    for d in xrange(jump[t]+1):
                        nr, nc = r+dr*d, c+dc*d
                        if not (0 <= nr < R and 0 <= nc < C and grid[nr][nc] != '#'):
                            break
                        graph[pos, t].add(nr*C + nc)

    degree = {}
    for m in xrange(N):
        for c in xrange(N):
            # degree[m, c, MOUSE] = len(graph[m, MOUSE])
            degree[m, c, CAT] = len(graph[c, CAT])
    color = collections.defaultdict(int)
    q1 = collections.deque()
    # q2 = collections.deque()
    for i in xrange(N):
        if i in WALLS or i == FOOD:
            continue
        color[FOOD, i, CAT] = MOUSE
        q1.append((FOOD, i, CAT))
        color[i, FOOD, MOUSE] = CAT
        # q2.append((i, FOOD, MOUSE))
        for t in [MOUSE, CAT]:
            color[i, i, t] = CAT
            # q2.append((i, i, t))
    while q1:
        i, j, t = q1.popleft()
        for ni, nj, nt in parents(i, j, t):
            if color[ni, nj, nt] != DRAW:
                continue
            if t == CAT:
                color[ni, nj, nt] = MOUSE
                q1.append((ni, nj, nt))
                continue
            degree[ni, nj, nt] -= 1
            if not degree[ni, nj, nt]:
                color[ni, nj, nt] = MOUSE
                q1.append((ni, nj, nt))
    # while q2:
    #     i, j, t = q2.popleft()
    #     for ni, nj, nt in parents(i, j, t):
    #         if color[ni, nj, nt] != DRAW:
    #             continue
    #         if t == MOUSE:
    #             color[ni, nj, nt] = CAT
    #             q2.append((ni, nj, nt))
    #             continue
    #         degree[ni, nj, nt] -= 1
    #         if not degree[ni, nj, nt]:
    #             color[ni, nj, nt] = CAT
    #             q2.append((ni, nj, nt))
    return color[MOUSE_START, CAT_START, MOUSE] == MOUSE


