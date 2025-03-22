def show_book(book_id):
    entries = calibre_db.get_book_read_archived(book_id, config.config_read_column, allow_show_archived=True)
    if entries:
        read_book = entries[1]
        archived_book = entries[2]
        entry = entries[0]
        entry.read_status = read_book == ub.ReadBook.STATUS_FINISHED
        entry.is_archived = archived_book
        for index in range(0, len(entry.languages)):
            entry.languages[index].language_name = isoLanguages.get_language_name(get_locale(), entry.languages[
                index].lang_code)
        cc = get_cc_columns(filter_config_custom_read=True)
        book_in_shelfs = []
        shelfs = ub.session.query(ub.BookShelf).filter(ub.BookShelf.book_id == book_id).all()
        for sh in shelfs:
            book_in_shelfs.append(sh.shelf)

        entry.tags = sort(entry.tags, key=lambda tag: tag.name)

        entry.ordered_authors = calibre_db.order_authors([entry])

        entry.kindle_list = check_send_to_kindle(entry)
        entry.reader_list = check_read_formats(entry)

        entry.audioentries = []
        for media_format in entry.data:
            if media_format.format.lower() in constants.EXTENSIONS_AUDIO:
                entry.audioentries.append(media_format.format.lower())

        return render_title_template('detail.html',
                                     entry=entry,
                                     cc=cc,
                                     is_xhr=request.headers.get('X-Requested-With')=='XMLHttpRequest',
                                     title=entry.title,
                                     books_shelfs=book_in_shelfs,
                                     page="book")
    else:
        log.debug(u"Oops! Selected book title is unavailable. File does not exist or is not accessible")
        flash(_(u"Oops! Selected book title is unavailable. File does not exist or is not accessible"),
              category="error")
        return redirect(url_for("web.index"))

def maximumMinutes(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    DIRECTIONS = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    FIRE, WALL, PERSON = range(1, 4)
    INF = 10**9
    def bfs(grid):
        time = {FIRE:[[INF]*len(grid[0]) for _ in xrange(len(grid))],
                PERSON:[[INF]*len(grid[0]) for _ in xrange(len(grid))]}
        d = 0
        q = [(r, c, FIRE) for r in xrange(len(grid)) for c in xrange(len(grid[0])) if grid[r][c] == FIRE]
        q.append((0, 0, PERSON))
        for r, c, t in q:
            time[t][r][c] = d
        while q:
            new_q = []
            for r, c, t in q:
                for dr, dc in DIRECTIONS:
                    nr, nc = r+dr, c+dc
                    if not (0 <= nr < len(grid) and 0 <= nc < len(grid[0]) and
                            grid[nr][nc] != WALL and time[t][nr][nc] == INF and
                            (t == FIRE or
                             d+1 < time[FIRE][nr][nc] or (d+1 == time[FIRE][nr][nc] and (nr, nc) == (len(grid)-1, len(grid[0])-1)))):
                        continue
                    time[t][nr][nc] = d+1
                    new_q.append((nr, nc, t))
            q = new_q
            d += 1
        return time

    time = bfs(grid)
    if time[PERSON][-1][-1] == INF:
        return -1
    if time[FIRE][-1][-1] == INF:
        return INF
    diff = time[FIRE][-1][-1]-time[PERSON][-1][-1]
    return diff if diff+2 in (time[FIRE][-1][-2]-time[PERSON][-1][-2], time[FIRE][-2][-1]-time[PERSON][-2][-1]) else diff-1


