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

def unhappyFriends(self, n, preferences, pairs):
    """
    :type n: int
    :type preferences: List[List[int]]
    :type pairs: List[List[int]]
    :rtype: int
    """
    friends = [[0]*n for _ in xrange(n)]
    for i in xrange(len(preferences)):
        for j in xrange(len(preferences[i])):
            friends[i][preferences[i][j]] = j
    pairing = [0]*n
    for i, j in pairs:
        pairing[i], pairing[j] = j, i
    return sum(any(friends[i][j] < friends[i][pairing[i]] and friends[j][i] < friends[j][pairing[j]]
                   for j in xrange(len(friends[i])) if j != i and j != pairing[i])
               for i in xrange(len(friends)))


