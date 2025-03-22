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

def minCost(self, startPos, homePos, rowCosts, colCosts):
    """
    :type startPos: List[int]
    :type homePos: List[int]
    :type rowCosts: List[int]
    :type colCosts: List[int]
    :rtype: int
    """
    [x0, y0], [x1, y1] = startPos, homePos
    return (sum(rowCosts[i] for i in xrange(min(x0, x1), max(x0, x1)+1))-rowCosts[x0]) + \
           (sum(colCosts[i] for i in xrange(min(y0, y1), max(y0, y1)+1))-colCosts[y0])


