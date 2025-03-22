def render_downloaded_books(page, order, user_id):
    if current_user.role_admin():
        user_id = int(user_id)
    else:
        user_id = current_user.id
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD):
        if current_user.show_detail_random():
            random = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                .order_by(func.random()).limit(config.config_random_books)
        else:
            random = false()

        entries, __, pagination = calibre_db.fill_indexpage(page,
                                                            0,
                                                            db.Books,
                                                            ub.Downloads.user_id == user_id,
                                                            order[0],
                                                            False, 0,
                                                            db.books_series_link,
                                                            db.Books.id == db.books_series_link.c.book,
                                                            db.Series,
                                                            ub.Downloads, db.Books.id == ub.Downloads.book_id)
        for book in entries:
            if not calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                             .filter(db.Books.id == book.id).first():
                ub.delete_download(book.id)
        user = ub.session.query(ub.User).filter(ub.User.id == user_id).first()
        return render_title_template('index.html',
                                     random=random,
                                     entries=entries,
                                     pagination=pagination,
                                     id=user_id,
                                     title=_(u"Downloaded books by %(user)s",user=user.name),
                                     page="download",
                                     order=order[1])
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


