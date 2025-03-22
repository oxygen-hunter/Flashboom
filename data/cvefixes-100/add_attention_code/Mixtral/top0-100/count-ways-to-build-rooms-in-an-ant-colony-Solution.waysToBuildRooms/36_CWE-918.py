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

def waysToBuildRooms(self, prevRoom):
    """
    :type prevRoom: List[int]
    :rtype: int
    """
    MOD = 10**9+7
    fact = [1, 1]
    inv = [0, 1]
    inv_fact = [1, 1]
    def nCr(n, k):
        while len(inv) <= n:  # lazy initialization
            fact.append(fact[-1]*len(inv) % MOD)
            inv.append(inv[MOD%len(inv)]*(MOD-MOD//len(inv)) % MOD)  # https://cp-algorithms.com/algebra/module-inverse.html
            inv_fact.append(inv_fact[-1]*inv[-1] % MOD)
        return (fact[n]*inv_fact[n-k] % MOD) * inv_fact[k] % MOD

    def dfs(adj, curr):
        total_ways, total_cnt = 1, 0
        for child in adj[curr]:
            ways, cnt = dfs(adj, child)
            total_cnt += cnt
            total_ways = (((total_ways*ways) % MOD)*nCr(total_cnt, cnt)) % MOD
        return total_ways, total_cnt+1

    adj = [[] for _ in xrange(len(prevRoom))]
    for i in xrange(1, len(prevRoom)):
        adj[prevRoom[i]].append(i)
    return dfs(adj, 0)[0]


