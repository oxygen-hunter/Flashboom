def download_list():
    if current_user.get_view_property('download', 'dir') == 'desc':
        order = ub.User.name.desc()
        order_no = 0
    else:
        order = ub.User.name.asc()
        order_no = 1
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD) and current_user.role_admin():
        entries = ub.session.query(ub.User, func.count(ub.Downloads.book_id).label('count'))\
            .join(ub.Downloads).group_by(ub.Downloads.user_id).order_by(order).all()
        charlist = ub.session.query(func.upper(func.substr(ub.User.name, 1, 1)).label('char')) \
            .filter(ub.User.role.op('&')(constants.ROLE_ANONYMOUS) != constants.ROLE_ANONYMOUS) \
            .group_by(func.upper(func.substr(ub.User.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Downloads"), page="downloadlist", data="download", order=order_no)
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


