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

def kSimilarity(self, A, B):
    """
    :type A: str
    :type B: str
    :rtype: int
    """
    def neighbors(s, B):
        for i, c in enumerate(s):
            if c != B[i]:
                break
        t = list(s)
        for j in xrange(i+1, len(s)):
            if t[j] == B[i]:
                t[i], t[j] = t[j], t[i]
                yield "".join(t)
                t[j], t[i] = t[i], t[j]

    q = collections.deque([A])
    lookup = set()
    result = 0
    while q:
        for _ in xrange(len(q)):
            s = q.popleft()
            if s == B:
                return result
            for t in neighbors(s, B):
                if t not in lookup:
                    lookup.add(t)
                    q.append(t)
        result += 1



