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

def deleteString(self, s):
    """
    :type s: str
    :rtype: int
    """
    MOD, P = 10**9+7, (113, 109)
    def hash(i, j):
        return [(prefix[idx][j+1]-prefix[idx][i]*power[idx][j-i+1])%MOD for idx in xrange(len(P))]

    if all(x == s[0] for x in s):
        return len(s)

    power = [[1] for _ in xrange(len(P))]
    prefix = [[0] for _ in xrange(len(P))]
    for x in s:
        for idx, p in enumerate(P):
            power[idx].append((power[idx][-1]*p)%MOD)
            prefix[idx].append((prefix[idx][-1]*p+(ord(x)-ord('a')))%MOD)
    dp = [1]*len(s)  # dp[i]: max operation count of s[i:]
    for i in reversed(xrange(len(s)-1)):
        for j in xrange(1, (len(s)-i)//2+1):
            if hash(i, i+j-1) == hash(i+j, i+2*j-1):
                dp[i] = max(dp[i], dp[i+j]+1)
    return dp[0]


