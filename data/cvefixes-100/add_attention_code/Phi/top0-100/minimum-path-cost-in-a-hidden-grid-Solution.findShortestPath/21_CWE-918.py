def extend_search_term(searchterm,
                       author_name,
                       book_title,
                       publisher,
                       pub_start,
                       pub_end,
                       tags,
                       rating_high,
                       rating_low,
                       read_status,
                       ):
    searchterm.extend((author_name.replace('|', ','), book_title, publisher))
    if pub_start:
        try:
            searchterm.extend([_(u"Published after ") +
                               format_date(datetime.strptime(pub_start, "%Y-%m-%d"),
                                           format='medium', locale=get_locale())])
        except ValueError:
            pub_start = u""
    if pub_end:
        try:
            searchterm.extend([_(u"Published before ") +
                               format_date(datetime.strptime(pub_end, "%Y-%m-%d"),
                                           format='medium', locale=get_locale())])
        except ValueError:
            pub_end = u""
    elements = {'tag': db.Tags, 'serie':db.Series, 'shelf':ub.Shelf}
    for key, db_element in elements.items():
        tag_names = calibre_db.session.query(db_element).filter(db_element.id.in_(tags['include_' + key])).all()
        searchterm.extend(tag.name for tag in tag_names)
        tag_names = calibre_db.session.query(db_element).filter(db_element.id.in_(tags['exclude_' + key])).all()
        searchterm.extend(tag.name for tag in tag_names)
    language_names = calibre_db.session.query(db.Languages). \
        filter(db.Languages.id.in_(tags['include_language'])).all()
    if language_names:
        language_names = calibre_db.speaking_language(language_names)
    searchterm.extend(language.name for language in language_names)
    language_names = calibre_db.session.query(db.Languages). \
        filter(db.Languages.id.in_(tags['exclude_language'])).all()
    if language_names:
        language_names = calibre_db.speaking_language(language_names)
    searchterm.extend(language.name for language in language_names)
    if rating_high:
        searchterm.extend([_(u"Rating <= %(rating)s", rating=rating_high)])
    if rating_low:
        searchterm.extend([_(u"Rating >= %(rating)s", rating=rating_low)])
    if read_status:
        searchterm.extend([_(u"Read Status = %(status)s", status=read_status)])
    searchterm.extend(ext for ext in tags['include_extension'])
    searchterm.extend(ext for ext in tags['exclude_extension'])
    # handle custom columns
    searchterm = " + ".join(filter(None, searchterm))
    return searchterm, pub_start, pub_end

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


