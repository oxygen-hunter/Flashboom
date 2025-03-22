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

def maxLength(self, ribbons, k):
    """
    :type ribbons: List[int]
    :type k: int
    :rtype: int
    """
    def check(ribbons, k, s):
        return reduce(lambda total,x: total+x//s, ribbons, 0) >= k

    left, right = 1, sum(ribbons)//k
    while left <= right:
        mid = left + (right-left)//2
        if not check(ribbons, k, mid):
            right = mid-1
        else:
            left = mid+1
    return right


