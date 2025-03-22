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

def freqAlphabets(self, s):
    """
    :type s: str
    :rtype: str
    """
    def alpha(num):
        return chr(ord('a') + int(num)-1)

    i = len(s)-1
    result = []
    while i >= 0:
        if s[i] == '#':
            result.append(alpha(s[i-2:i]))
            i -= 3
        else:
            result.append(alpha(s[i]))
            i -= 1
    return "".join(reversed(result))



