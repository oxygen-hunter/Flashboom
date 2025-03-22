def extend_search_term(searchterm,
                       author_name,
                       book_title,
                       publisher,
                       pub_start,
                       pub_end,
                       tags,
                       rating_high,
                       rating_low,
                       read_status,
                       ):
    searchterm.extend((author_name.replace('|', ','), book_title, publisher))
    if pub_start:
        try:
            searchterm.extend([_(u"Published after ") +
                               format_date(datetime.strptime(pub_start, "%Y-%m-%d"),
                                           format='medium', locale=get_locale())])
        except ValueError:
            pub_start = u""
    if pub_end:
        try:
            searchterm.extend([_(u"Published before ") +
                               format_date(datetime.strptime(pub_end, "%Y-%m-%d"),
                                           format='medium', locale=get_locale())])
        except ValueError:
            pub_end = u""
    elements = {'tag': db.Tags, 'serie':db.Series, 'shelf':ub.Shelf}
    for key, db_element in elements.items():
        tag_names = calibre_db.session.query(db_element).filter(db_element.id.in_(tags['include_' + key])).all()
        searchterm.extend(tag.name for tag in tag_names)
        tag_names = calibre_db.session.query(db_element).filter(db_element.id.in_(tags['exclude_' + key])).all()
        searchterm.extend(tag.name for tag in tag_names)
    language_names = calibre_db.session.query(db.Languages). \
        filter(db.Languages.id.in_(tags['include_language'])).all()
    if language_names:
        language_names = calibre_db.speaking_language(language_names)
    searchterm.extend(language.name for language in language_names)
    language_names = calibre_db.session.query(db.Languages). \
        filter(db.Languages.id.in_(tags['exclude_language'])).all()
    if language_names:
        language_names = calibre_db.speaking_language(language_names)
    searchterm.extend(language.name for language in language_names)
    if rating_high:
        searchterm.extend([_(u"Rating <= %(rating)s", rating=rating_high)])
    if rating_low:
        searchterm.extend([_(u"Rating >= %(rating)s", rating=rating_low)])
    if read_status:
        searchterm.extend([_(u"Read Status = %(status)s", status=read_status)])
    searchterm.extend(ext for ext in tags['include_extension'])
    searchterm.extend(ext for ext in tags['exclude_extension'])
    # handle custom columns
    searchterm = " + ".join(filter(None, searchterm))
    return searchterm, pub_start, pub_end

def minimumCost(self, n, edges, query):
    """
    :type n: int
    :type edges: List[List[int]]
    :type query: List[List[int]]
    :rtype: List[int]
    """
    class UnionFind(object):  # Time: O(n * alpha(n)), Space: O(n)
        def __init__(self, n):
            self.set = list(range(n))
            self.rank = [0]*n
            self.w = [-1]*n  # added

        def find_set(self, x):
            stk = []
            while self.set[x] != x:  # path compression
                stk.append(x)
                x = self.set[x]
            while stk:
                self.set[stk.pop()] = x
            return x

        def union_set(self, x, y, w):  # modified
            x, y = self.find_set(x), self.find_set(y)
            if x == y:
                self.w[x] &= w  # added
                return False
            if self.rank[x] > self.rank[y]:  # union by rank
                x, y = y, x
            self.set[x] = self.set[y]
            if self.rank[x] == self.rank[y]:
                self.rank[y] += 1
            self.w[y] &= self.w[x]&w  # added
            return True
        
        def cost(self, x):  # added
            return self.w[self.find_set(x)]

    uf = UnionFind(n)
    for u, v, w in edges:
        uf.union_set(u, v, w)
    result = [-1]*(len(query))
    for i, (s, t) in enumerate(query):
        if uf.find_set(s) != uf.find_set(t):
            continue
        result[i] = uf.cost(s) if s != t else 0
    return result


