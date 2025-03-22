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


