def render_archived_books(page, sort_param):
    order = sort_param[0] or []
    archived_books = (
        ub.session.query(ub.ArchivedBook)
        .filter(ub.ArchivedBook.user_id == int(current_user.id))
        .filter(ub.ArchivedBook.is_archived == True)
        .all()
    )
    archived_book_ids = [archived_book.book_id for archived_book in archived_books]

    archived_filter = db.Books.id.in_(archived_book_ids)

    entries, random, pagination = calibre_db.fill_indexpage_with_archived_books(page, db.Books,
                                                                                0,
                                                                                archived_filter,
                                                                                order,
                                                                                True,
                                                                                False, 0)

    name = _(u'Archived Books') + ' (' + str(len(archived_book_ids)) + ')'
    pagename = "archived"
    return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                 title=name, page=pagename, order=sort_param[1])

def minCost(self, n, roads, appleCost, k):
    """
    :type n: int
    :type roads: List[List[int]]
    :type appleCost: List[int]
    :type k: int
    :rtype: List[int]
    """
    def dijkstra(start):
        best = [float("inf")]*len(adj)
        best[start] = 0
        min_heap = [(0, start)]
        while min_heap:
            curr, u = heapq.heappop(min_heap)
            if best[u] < curr:
                continue
            for v, w in adj[u]:                
                if best[v] <= curr+w:
                    continue
                best[v] = curr+w
                heapq.heappush(min_heap, (curr+w, v))
        return best

    adj = [[] for _ in xrange(n)]
    for a, b, c in roads:
        adj[a-1].append((b-1, c))
        adj[b-1].append((a-1, c))
    return [min(a+d*(k+1) for a, d in itertools.izip(appleCost, dijkstra(u))) for u in xrange(n)]


