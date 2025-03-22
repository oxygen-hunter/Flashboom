def category_list():
    if current_user.check_visibility(constants.SIDEBAR_CATEGORY):
        if current_user.get_view_property('category', 'dir') == 'desc':
            order = db.Tags.name.desc()
            order_no = 0
        else:
            order = db.Tags.name.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Tags, func.count('books_tags_link.book').label('count')) \
            .join(db.books_tags_link).join(db.Books).order_by(order).filter(calibre_db.common_filters()) \
            .group_by(text('books_tags_link.tag')).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Tags.name, 1, 1)).label('char')) \
            .join(db.books_tags_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Tags.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Categories"), page="catlist", data="category", order=order_no)
    else:
        abort(404)

def remainingMethods(self, n, k, invocations):
    """
    :type n: int
    :type k: int
    :type invocations: List[List[int]]
    :rtype: List[int]
    """
    def bfs():
        lookup = [False]*n
        lookup[k] = True
        q = [k]
        while q:
            new_q = []
            for u in q:
                for v in adj[u]:
                    if lookup[v]:
                        continue
                    lookup[v] = True
                    new_q.append(v)
            q = new_q
        return lookup

    adj = [[] for _ in xrange(n)]
    for u, v in invocations:
        adj[u].append(v)
    lookup = bfs()
    return [u for u in xrange(n) if not lookup[u]] if all(lookup[u] == lookup[v] for u, v in invocations) else range(n)


