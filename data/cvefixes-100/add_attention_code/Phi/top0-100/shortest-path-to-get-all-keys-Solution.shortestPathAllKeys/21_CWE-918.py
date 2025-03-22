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

def shortestPathAllKeys(self, grid):
    """
    :type grid: List[str]
    :rtype: int
    """
    directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]

    def bfs(grid, source, locations):
        r, c = locations[source]
        lookup = [[False]*(len(grid[0])) for _ in xrange(len(grid))]
        lookup[r][c] = True
        q = collections.deque([(r, c, 0)])
        dist = {}
        while q:
            r, c, d = q.popleft()
            if source != grid[r][c] != '.':
                dist[grid[r][c]] = d
                continue
            for direction in directions:
                cr, cc = r+direction[0], c+direction[1]
                if not ((0 <= cr < len(grid)) and
                        (0 <= cc < len(grid[cr]))):
                    continue
                if grid[cr][cc] != '#' and not lookup[cr][cc]:
                    lookup[cr][cc] = True
                    q.append((cr, cc, d+1))
        return dist

    locations = {place: (r, c)
                 for r, row in enumerate(grid)
                 for c, place in enumerate(row)
                 if place not in '.#'}
    dists = {place: bfs(grid, place, locations) for place in locations}

    # Dijkstra's algorithm
    min_heap = [(0, '@', 0)]
    best = collections.defaultdict(lambda: collections.defaultdict(
                                               lambda: float("inf")))
    best['@'][0] = 0
    target_state = 2**sum(place.islower() for place in locations)-1
    while min_heap:
        cur_d, place, state = heapq.heappop(min_heap)
        if best[place][state] < cur_d:
            continue
        if state == target_state:
            return cur_d
        for dest, d in dists[place].iteritems():
            next_state = state
            if dest.islower():
                next_state |= (1 << (ord(dest)-ord('a')))
            elif dest.isupper():
                if not (state & (1 << (ord(dest)-ord('A')))):
                    continue
            if cur_d+d < best[dest][next_state]:
                best[dest][next_state] = cur_d+d
                heapq.heappush(min_heap, (cur_d+d, dest, next_state))
    return -1



