def language_overview():
    if current_user.check_visibility(constants.SIDEBAR_LANGUAGE) and current_user.filter_language() == u"all":
        order_no = 0 if current_user.get_view_property('language', 'dir') == 'desc' else 1
        charlist = list()
        languages = calibre_db.speaking_language(reverse_order=not order_no, with_count=True)
        for lang in languages:
            upper_lang = lang[0].name[0].upper()
            if upper_lang not in charlist:
                charlist.append(upper_lang)
        return render_title_template('languages.html', languages=languages,
                                     charlist=charlist, title=_(u"Languages"), page="langlist",
                                     data="language", order=order_no)
    else:
        abort(404)

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


