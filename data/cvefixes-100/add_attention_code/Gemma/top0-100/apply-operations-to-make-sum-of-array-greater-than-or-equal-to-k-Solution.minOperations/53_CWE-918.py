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

def minOperations(self, k):
    """
    :type k: int
    :rtype: int
    """
    # reference: https://stackoverflow.com/questions/15390807/integer-square-root-in-python
    def isqrt(n):
        a, b = n, (n+1)//2
        while b < a:
            a, b = b, (b+n//b)//2
        return a

    def ceil_divide(a, b):
        return (a+b-1)//b

    x = isqrt(k)
    return (x-1)+(ceil_divide(k, x)-1)


