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

def maxProbability(self, n, edges, succProb, start, end):
    """
    :type n: int
    :type edges: List[List[int]]
    :type succProb: List[float]
    :type start: int
    :type end: int
    :rtype: float
    """
    adj = collections.defaultdict(list)
    for (u, v), p in itertools.izip(edges, succProb):
        adj[u].append((v, p))
        adj[v].append((u, p))
    max_heap = [(-1.0, start)]
    result, lookup = collections.defaultdict(float), set()
    result[start] = 1.0
    while max_heap and len(lookup) != len(adj):
        curr, u = heapq.heappop(max_heap)
        if u in lookup:
            continue
        lookup.add(u)
        for v, w in adj[u]:
            if v in lookup:
                continue
            if v in result and result[v] >= -curr*w:
                continue
            result[v] = -curr*w
            heapq.heappush(max_heap, (-result[v], v))
    return result[end]


