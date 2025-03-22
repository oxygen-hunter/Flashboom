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

def totalMoney(self, n):
    """
    :type n: int
    :rtype: int
    """
    def arithmetic_sequence_sum(a, d, n):
        return (2*a + (n-1)*d) * n //2

    cost, day = 1, 7
    first_week_cost = arithmetic_sequence_sum(cost, cost, day)
    week, remain_day = divmod(n, day)
    return arithmetic_sequence_sum(first_week_cost, cost*day, week) + \
           arithmetic_sequence_sum(cost*(week+1), cost, remain_day)


