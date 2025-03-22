def publisher_list():
    if current_user.get_view_property('publisher', 'dir') == 'desc':
        order = db.Publishers.name.desc()
        order_no = 0
    else:
        order = db.Publishers.name.asc()
        order_no = 1
    if current_user.check_visibility(constants.SIDEBAR_PUBLISHER):
        entries = calibre_db.session.query(db.Publishers, func.count('books_publishers_link.book').label('count')) \
            .join(db.books_publishers_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_publishers_link.publisher')).order_by(order).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Publishers.name, 1, 1)).label('char')) \
            .join(db.books_publishers_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Publishers.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Publishers"), page="publisherlist", data="publisher", order=order_no)
    else:
        abort(404)

def maximumInvitations(self, favorite):
    """
    :type favorite: List[int]
    :rtype: int
    """
    def find_cycles(adj):
        result = []
        lookup = [False]*len(adj)
        for u in xrange(len(adj)):
            cnt = {}
            while not lookup[u]:
                lookup[u] = True
                cnt[u] = len(cnt)
                u = adj[u]
            if u in cnt:
                result.append((u, len(cnt)-cnt[u]))
        return result

    def bfs(adj, u, exclude):
        result = 0
        q = [u]
        while q:
            result += 1
            new_q = []
            for u in q:
                for v in adj[u]:
                    if v == exclude:
                        continue
                    new_q.append(v)
            q = new_q
        return result
        
    inv_adj = [[] for _ in xrange(len(favorite))]  
    for u, v in enumerate(favorite):
        inv_adj[v].append(u)
    cycles = find_cycles(favorite)
    return max(max([l for _, l in cycles if l > 2] or [0]),
               sum(bfs(inv_adj, u, favorite[u]) + bfs(inv_adj, favorite[u], u) for u, l in cycles if l == 2))


