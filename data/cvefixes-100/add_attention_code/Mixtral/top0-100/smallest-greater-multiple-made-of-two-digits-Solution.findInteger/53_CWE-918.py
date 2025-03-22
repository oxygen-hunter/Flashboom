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

def findInteger(self, k, digit1, digit2):
    """
    :type k: int
    :type digit1: int
    :type digit2: int
    :rtype: int
    """
    MAX_NUM_OF_DIGITS = 10
    INT_MAX = 2**31-1

    if digit1 < digit2:
        digit1, digit2 = digit2, digit1
    total = 2
    for l in xrange(1, MAX_NUM_OF_DIGITS+1):
        for mask in xrange(total):
            curr, bit = 0, total>>1
            while bit:
                curr = curr*10 + (digit1 if mask&bit else digit2)
                bit >>= 1
            if k < curr <= INT_MAX and curr%k == 0:
                return curr
        total <<= 1
    return -1


