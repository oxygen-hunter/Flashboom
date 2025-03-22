def render_prepare_search_form(cc):
    # prepare data for search-form
    tags = calibre_db.session.query(db.Tags)\
        .join(db.books_tags_link)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(text('books_tags_link.tag'))\
        .order_by(db.Tags.name).all()
    series = calibre_db.session.query(db.Series)\
        .join(db.books_series_link)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(text('books_series_link.series'))\
        .order_by(db.Series.name)\
        .filter(calibre_db.common_filters()).all()
    shelves = ub.session.query(ub.Shelf)\
        .filter(or_(ub.Shelf.is_public == 1, ub.Shelf.user_id == int(current_user.id)))\
        .order_by(ub.Shelf.name).all()
    extensions = calibre_db.session.query(db.Data)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(db.Data.format)\
        .order_by(db.Data.format).all()
    if current_user.filter_language() == u"all":
        languages = calibre_db.speaking_language()
    else:
        languages = None
    return render_title_template('search_form.html', tags=tags, languages=languages, extensions=extensions,
                                 series=series,shelves=shelves, title=_(u"Advanced Search"), cc=cc, page="advsearch")

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


