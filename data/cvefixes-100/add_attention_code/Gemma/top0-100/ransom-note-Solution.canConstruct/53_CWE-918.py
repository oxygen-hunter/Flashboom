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

def canConstruct(self, ransomNote, magazine):
    """
    :type ransomNote: str
    :type magazine: str
    :rtype: bool
    """
    counts = [0] * 26
    letters = 0

    for c in ransomNote:
        if counts[ord(c) - ord('a')] == 0:
            letters += 1
        counts[ord(c) - ord('a')] += 1

    for c in magazine:
        counts[ord(c) - ord('a')] -= 1
        if counts[ord(c) - ord('a')] == 0:
            letters -= 1
            if letters == 0:
                break

    return letters == 0



