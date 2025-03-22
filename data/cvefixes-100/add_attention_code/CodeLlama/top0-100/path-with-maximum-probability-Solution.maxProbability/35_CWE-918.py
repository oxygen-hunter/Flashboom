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


