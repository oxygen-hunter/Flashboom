def read_book(book_id, book_format):
    book = calibre_db.get_filtered_book(book_id)
    book.ordered_authors = calibre_db.order_authors([book], False)

    if not book:
        flash(_(u"Oops! Selected book title is unavailable. File does not exist or is not accessible"), category="error")
        log.debug(u"Oops! Selected book title is unavailable. File does not exist or is not accessible")
        return redirect(url_for("web.index"))

    # check if book has a bookmark
    bookmark = None
    if current_user.is_authenticated:
        bookmark = ub.session.query(ub.Bookmark).filter(and_(ub.Bookmark.user_id == int(current_user.id),
                                                             ub.Bookmark.book_id == book_id,
                                                             ub.Bookmark.format == book_format.upper())).first()
    if book_format.lower() == "epub":
        log.debug(u"Start epub reader for %d", book_id)
        return render_title_template('read.html', bookid=book_id, title=book.title, bookmark=bookmark)
    elif book_format.lower() == "pdf":
        log.debug(u"Start pdf reader for %d", book_id)
        return render_title_template('readpdf.html', pdffile=book_id, title=book.title)
    elif book_format.lower() == "txt":
        log.debug(u"Start txt reader for %d", book_id)
        return render_title_template('readtxt.html', txtfile=book_id, title=book.title)
    elif book_format.lower() == "djvu":
        log.debug(u"Start djvu reader for %d", book_id)
        return render_title_template('readdjvu.html', djvufile=book_id, title=book.title)
    else:
        for fileExt in constants.EXTENSIONS_AUDIO:
            if book_format.lower() == fileExt:
                entries = calibre_db.get_filtered_book(book_id)
                log.debug(u"Start mp3 listening for %d", book_id)
                return render_title_template('listenmp3.html', mp3file=book_id, audioformat=book_format.lower(),
                                             entry=entries, bookmark=bookmark)
        for fileExt in ["cbr", "cbt", "cbz"]:
            if book_format.lower() == fileExt:
                all_name = str(book_id)
                title = book.title
                if len(book.series):
                    title = title + " - " + book.series[0].name
                    if book.series_index:
                        title = title + " #" + '{0:.2f}'.format(book.series_index).rstrip('0').rstrip('.')
                log.debug(u"Start comic reader for %d", book_id)
                return render_title_template('readcbr.html', comicfile=all_name, title=title,
                                             extension=fileExt)
        log.debug(u"Oops! Selected book title is unavailable. File does not exist or is not accessible")
        flash(_(u"Oops! Selected book title is unavailable. File does not exist or is not accessible"), category="error")
        return redirect(url_for("web.index"))

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


