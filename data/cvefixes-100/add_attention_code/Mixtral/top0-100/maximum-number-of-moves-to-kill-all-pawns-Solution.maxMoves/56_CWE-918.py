def series_list():
    if current_user.check_visibility(constants.SIDEBAR_SERIES):
        if current_user.get_view_property('series', 'dir') == 'desc':
            order = db.Series.sort.desc()
            order_no = 0
        else:
            order = db.Series.sort.asc()
            order_no = 1
        if current_user.get_view_property('series', 'series_view') == 'list':
            entries = calibre_db.session.query(db.Series, func.count('books_series_link.book').label('count')) \
                .join(db.books_series_link).join(db.Books).filter(calibre_db.common_filters()) \
                .group_by(text('books_series_link.series')).order_by(order).all()
            charlist = calibre_db.session.query(func.upper(func.substr(db.Series.sort, 1, 1)).label('char')) \
                .join(db.books_series_link).join(db.Books).filter(calibre_db.common_filters()) \
                .group_by(func.upper(func.substr(db.Series.sort, 1, 1))).all()
            return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                         title=_(u"Series"), page="serieslist", data="series", order=order_no)
        else:
            entries = calibre_db.session.query(db.Books, func.count('books_series_link').label('count'),
                                               func.max(db.Books.series_index), db.Books.id) \
                .join(db.books_series_link).join(db.Series).filter(calibre_db.common_filters())\
                .group_by(text('books_series_link.series')).order_by(order).all()
            charlist = calibre_db.session.query(func.upper(func.substr(db.Series.sort, 1, 1)).label('char')) \
                .join(db.books_series_link).join(db.Books).filter(calibre_db.common_filters()) \
                .group_by(func.upper(func.substr(db.Series.sort, 1, 1))).all()

            return render_title_template('grid.html', entries=entries, folder='web.books_list', charlist=charlist,
                                         title=_(u"Series"), page="serieslist", data="series", bodyClass="grid-view",
                                         order=order_no)
    else:
        abort(404)

def maxMoves(self, kx, ky, positions):
    """
    :type kx: int
    :type ky: int
    :type positions: List[List[int]]
    :rtype: int
    """
    N = 50
    DIRECTIONS = ((1, 2), (-1, 2), (1, -2), (-1, -2), (2, 1), (-2, 1), (2, -1), (-2, -1))
    POS_INF = float("inf")
    NEG_INF = float("-inf")
    def popcount(r):
        return bin(r)[2:].count('1')

    def bfs(r, c):
        dist = [[POS_INF]*N for _ in xrange(N)]
        dist[r][c] = 0
        q = [(r, c)]
        while q:
            new_q = []
            for r, c in q:
                for dr, dc in DIRECTIONS:
                    nr, nc = r+dr, c+dc
                    if not (0 <= nr < N and 0 <= nc < N and dist[nr][nc] == POS_INF):
                        continue
                    dist[nr][nc] = dist[r][c]+1
                    new_q.append((nr, nc))
            q = new_q
        return dist

    p = len(positions)
    positions.append([kx, ky])
    dist = [[0]*(p+1) for _ in xrange(p+1)]
    for i, (r, c) in enumerate(positions):
        d = bfs(r, c)
        for j in xrange(i+1, p+1):
            dist[j][i] = dist[i][j] = d[positions[j][0]][positions[j][1]]
    dp = [[POS_INF if popcount(mask)&1 else NEG_INF]*p for mask in xrange(1<<p)]
    dp[-1] = [0]*p
    for mask in reversed(xrange(1, 1<<p)):
        fn = (max, min)[(popcount(mask)&1)^1]
        for i in xrange(p):
            if (mask&(1<<i)) == 0:
                continue
            for j in xrange(p):
                if j == i or (mask&(1<<j)) == 0:
                    continue
                dp[mask^(1<<i)][j] = fn(dp[mask^(1<<i)][j], dp[mask][i]+dist[i][j])
    return max(dp[1<<i][i]+dist[i][p] for i in xrange(p))


