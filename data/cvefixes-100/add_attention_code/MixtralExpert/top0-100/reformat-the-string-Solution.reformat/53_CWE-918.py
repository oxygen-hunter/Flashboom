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

def reformat(self, s):
    """
    :type s: str
    :rtype: str
    """
    def char_gen(start, end, count):
        for c in xrange(ord(start), ord(end)+1):
            c = chr(c)
            for i in xrange(count[c]):
                yield c
        yield ''

    count = collections.defaultdict(int)
    alpha_cnt = 0
    for c in s:
        count[c] += 1
        if c.isalpha():
            alpha_cnt += 1
    if abs(len(s)-2*alpha_cnt) > 1:
        return ""

    result = []
    it1, it2 = char_gen('a', 'z', count), char_gen('0', '9', count)
    if alpha_cnt < len(s)-alpha_cnt:
        it1, it2 = it2, it1
    while len(result) < len(s):
        result.append(next(it1))
        result.append(next(it2))
    return "".join(result)


