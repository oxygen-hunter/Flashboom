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

def timeTaken(self, arrival, state):
    """
    :type arrival: List[int]
    :type state: List[int]
    :rtype: List[int]
    """
    def go_until(t):
        while curr[0] <= t and any(q):
            if not q[direction[0]]:
                direction[0] ^= 1
            result[q[direction[0]].popleft()] = curr[0]
            curr[0] += 1

    UNKNOWN, ENTERING, EXITING = range(-1, 1+1)
    result = [0]*len(arrival)
    curr, direction = [float("-inf")], [UNKNOWN]
    q = [collections.deque(), collections.deque()]
    for i, (a, s) in enumerate(itertools.izip(arrival, state)):
        go_until(a-1)
        q[s].append(i)
        if not (a <= curr[0]):
            curr, direction = [a], [EXITING]
    go_until(float("inf"))
    return result


