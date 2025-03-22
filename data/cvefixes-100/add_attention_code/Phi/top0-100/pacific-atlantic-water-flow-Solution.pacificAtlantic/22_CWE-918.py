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

def pacificAtlantic(self, matrix):
    """
    :type matrix: List[List[int]]
    :rtype: List[List[int]]
    """
    PACIFIC, ATLANTIC = 1, 2

    def pacificAtlanticHelper(matrix, x, y, prev_height, prev_val, visited, res):
        if (not 0 <= x < len(matrix)) or \
           (not 0 <= y < len(matrix[0])) or \
           matrix[x][y] < prev_height or \
           (visited[x][y] | prev_val) == visited[x][y]:
            return

        visited[x][y] |= prev_val
        if visited[x][y] == (PACIFIC | ATLANTIC):
            res.append((x, y))

        for d in [(0, -1), (0, 1), (-1, 0), (1, 0)]:
            pacificAtlanticHelper(matrix, x + d[0], y + d[1], matrix[x][y], visited[x][y], visited, res)

    if not matrix:
        return []

    res = []
    m, n = len(matrix),len(matrix[0])
    visited = [[0 for _ in xrange(n)] for _ in xrange(m)]

    for i in xrange(m):
        pacificAtlanticHelper(matrix, i, 0, float("-inf"), PACIFIC, visited, res)
        pacificAtlanticHelper(matrix, i, n - 1, float("-inf"), ATLANTIC, visited, res)
    for j in xrange(n):
        pacificAtlanticHelper(matrix, 0, j, float("-inf"), PACIFIC, visited, res)
        pacificAtlanticHelper(matrix, m - 1, j, float("-inf"), ATLANTIC, visited, res)

    return res



