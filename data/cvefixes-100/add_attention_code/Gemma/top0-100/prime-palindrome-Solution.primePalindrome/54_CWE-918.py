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

def primePalindrome(self, N):
    """
    :type N: int
    :rtype: int
    """
    def is_prime(n):
        if n < 2 or n % 2 == 0:
            return n == 2
        return all(n % d for d in xrange(3, int(n**.5) + 1, 2))

    if 8 <= N <= 11:
        return 11
    for i in xrange(10**(len(str(N))//2), 10**5):
        j = int(str(i) + str(i)[-2::-1])
        if j >= N and is_prime(j):
            return j



