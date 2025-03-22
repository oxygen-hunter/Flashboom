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

def findShortestPath(self, master):
    """
    :type master: GridMaster
    :rtype: int
    """
    directions = {'L': (0, -1), 'R': (0, 1), 'U': (-1, 0), 'D': (1, 0)}
    rollback = {'L': 'R', 'R': 'L', 'U': 'D', 'D': 'U'}

    def dfs(pos, target, master, lookup, adj):
        if target[0] is None and master.isTarget():
            target[0] = pos
        lookup.add(pos)
        for d, (di, dj) in directions.iteritems():
            if not master.canMove(d):
                continue
            nei = (pos[0]+di, pos[1]+dj)
            if nei in adj[pos]:
                continue
            adj[pos][nei] = master.move(d)
            if nei not in lookup:
                dfs(nei, target, master, lookup, adj)
            adj[nei][pos] = master.move(rollback[d])
                    
    def dijkstra(adj, start, target):
        dist = {start:0}
        min_heap = [(0, start)]
        while min_heap:
            curr, u = heapq.heappop(min_heap)
            if dist[u] < curr:
                continue
            for v, w in adj[u].iteritems():
                if v in dist and dist[v] <= curr+w:
                    continue
                dist[v] = curr+w
                heapq.heappush(min_heap, (curr+w, v))
        return dist[target] if target in dist else -1 
    
    start = (0, 0)
    target = [None]
    adj = collections.defaultdict(dict)
    dfs(start, target, master, set(), adj)
    if not target[0]:
        return -1
    return dijkstra(adj, start, target[0])


