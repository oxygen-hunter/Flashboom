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

def shortestBridge(self, A):
    """
    :type A: List[List[int]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    def get_islands(A):
        islands = []
        done = set()
        for r, row in enumerate(A):
            for c, val in enumerate(row):
                if val == 0 or (r, c) in done:
                    continue
                s = [(r, c)]
                lookup = set(s)
                while s:
                    node = s.pop()
                    for d in directions:
                        nei = node[0]+d[0], node[1]+d[1]
                        if not (0 <= nei[0] < len(A) and 0 <= nei[1] < len(A[0])) or \
                           nei in lookup or A[nei[0]][nei[1]] == 0:
                            continue
                        s.append(nei)
                        lookup.add(nei)
                done |= lookup
                islands.append(lookup)
                if len(islands) == 2:
                    break
        return islands

    lookup, target = get_islands(A)
    q = collections.deque([(node, 0) for node in lookup])
    while q:
        node, dis = q.popleft()
        if node in target:
            return dis-1
        for d in directions:
            nei = node[0]+d[0], node[1]+d[1]
            if not (0 <= nei[0] < len(A) and 0 <= nei[1] < len(A[0])) or \
               nei in lookup:
                continue
            q.append((nei, dis+1))
            lookup.add(nei)


