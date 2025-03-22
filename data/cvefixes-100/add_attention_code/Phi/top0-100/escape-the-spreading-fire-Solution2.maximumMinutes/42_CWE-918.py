def render_archived_books(page, sort_param):
    order = sort_param[0] or []
    archived_books = (
        ub.session.query(ub.ArchivedBook)
        .filter(ub.ArchivedBook.user_id == int(current_user.id))
        .filter(ub.ArchivedBook.is_archived == True)
        .all()
    )
    archived_book_ids = [archived_book.book_id for archived_book in archived_books]

    archived_filter = db.Books.id.in_(archived_book_ids)

    entries, random, pagination = calibre_db.fill_indexpage_with_archived_books(page, db.Books,
                                                                                0,
                                                                                archived_filter,
                                                                                order,
                                                                                True,
                                                                                False, 0)

    name = _(u'Archived Books') + ' (' + str(len(archived_book_ids)) + ')'
    pagename = "archived"
    return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                 title=name, page=pagename, order=sort_param[1])

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


