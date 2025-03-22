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

def union_set(self, x, y, v):  # modified
    x, y = self.find_set(x), self.find_set(y)
    if x == y:
        return 0  # modified
    if self.rank[x] > self.rank[y]:  # union by rank
        x, y = y, x
    self.set[x] = self.set[y]
    if self.rank[x] == self.rank[y]:
        self.rank[y] += 1
    cx, cy = self.cnt[x][v], self.cnt[y][v]  # added
    self.cnt[y] = collections.Counter({v:cx+cy})  # added
    return cx*cy  # modified



