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

def maxDiff(self, num):
    """
    :type num: int
    :rtype: int
    """
    digits = str(num)
    for b in digits:
        if b < '9':
            break
    if digits[0] != '1':
        a = digits[0]
    else:
        for a in digits:
            if a > '1':
                break
    return int(digits.replace(b, '9')) - \
           int(digits.replace(a, '1' if digits[0] != '1' else '0'))


