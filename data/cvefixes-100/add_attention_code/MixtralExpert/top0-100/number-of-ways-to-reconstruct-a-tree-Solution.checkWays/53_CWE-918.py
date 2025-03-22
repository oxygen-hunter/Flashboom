def render_search_results(term, offset=None, order=None, limit=None):
    join = db.books_series_link, db.Books.id == db.books_series_link.c.book, db.Series
    entries, result_count, pagination = calibre_db.get_search_results(term,
                                                                      offset,
                                                                      order,
                                                                      limit,
                                                                      False,
                                                                      config.config_read_column,
                                                                      *join)
    return render_title_template('search.html',
                                 searchterm=term,
                                 pagination=pagination,
                                 query=term,
                                 adv_searchterm=term,
                                 entries=entries,
                                 result_count=result_count,
                                 title=_(u"Search"),
                                 page="search",
                                 order=order[1])

def checkWays(self, pairs):
    """
    :type pairs: List[List[int]]
    :rtype: int
    """
    adj = collections.defaultdict(set)
    for x, y in pairs:
        adj[x].add(y)
        adj[y].add(x)
    n, mul = len(adj), False
    lookup = set()
    for node in sorted(adj.iterkeys(), key=lambda i: len(adj[i]), reverse=True):
        lookup.add(node)
        parent = 0
        for x in adj[node]:
            if x not in lookup:
                continue
            if parent == 0 or len(adj[x]) < len(adj[parent]):
                parent = x
        if parent:
            if any(True for x in adj[node] if x != parent and x not in adj[parent]):
                return 0
            mul |= len(adj[parent]) == len(adj[node])
        elif len(adj[node]) != n-1:
            return 0
    return 1 + mul


