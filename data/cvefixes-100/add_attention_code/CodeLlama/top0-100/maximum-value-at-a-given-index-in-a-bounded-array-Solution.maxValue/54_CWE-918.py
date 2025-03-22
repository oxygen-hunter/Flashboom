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

def maxValue(self, n, index, maxSum):
    """
    :type n: int
    :type index: int
    :type maxSum: int
    :rtype: int
    """
    def check(n, index, maxSum, x):
        y = max(x-index, 0)
        total = (x+y)*(x-y+1)//2
        y = max(x-((n-1)-index), 0)
        total += (x+y)*(x-y+1)//2
        return total-x <= maxSum

    maxSum -= n
    left, right = 0, maxSum
    while left <= right:
        mid = left + (right-left)//2
        if not check(n, index, maxSum, mid):
            right = mid-1
        else:
            left = mid+1
    return 1+right


