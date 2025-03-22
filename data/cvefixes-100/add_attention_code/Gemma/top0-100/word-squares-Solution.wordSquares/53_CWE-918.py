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

def wordSquares(self, words):
    """
    :type words: List[str]
    :rtype: List[List[str]]
    """
    result = []

    trie = TrieNode()
    for i in xrange(len(words)):
        trie.insert(words, i)

    curr = []
    for s in words:
        curr.append(s)
        self.wordSquaresHelper(words, trie, curr, result)
        curr.pop()

    return result



