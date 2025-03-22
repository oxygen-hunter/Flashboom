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

def secondMinimum(self, n, edges, time, change):
    """
    :type n: int
    :type edges: List[List[int]]
    :type time: int
    :type change: int
    :rtype: int
    """
    INF = float("inf")
    def bfs(adj, start):
        q = [start]
        dist = [INF]*len(adj)
        dist[start] = 0
        while q:
            new_q = []
            for u in q:
                for v in adj[u]:
                    if dist[v] != INF:
                        continue
                    dist[v] = dist[u]+1
                    new_q.append(v)
            q = new_q
        return dist

    def calc_time(time, change, dist):
        result = 0
        for _ in xrange(dist):
            if result//change%2:
                result = (result//change+1)*change
            result += time
        return result

    adj = [[] for _ in xrange(n)]
    for u, v in edges:
        adj[u-1].append(v-1)
        adj[v-1].append(u-1)
    dist_to_end, dist_to_start = bfs(adj, 0), bfs(adj, n-1)

    dist = dist_to_end[n-1]+2  # always exists
    for i in xrange(n):  # case of detour
        if dist_to_end[i]+dist_to_start[i] == dist_to_end[n-1]:
            continue
        dist = min(dist, dist_to_end[i]+dist_to_start[i])  # find second min
        if dist == dist_to_end[n-1]+1:
            break
    return calc_time(time, change, dist)


