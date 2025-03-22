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

def numberOfAlternatingGroups(self, colors, queries):
    """
    :type colors: List[int]
    :type queries: List[List[int]]
    :rtype: List[int]
    """
    class BIT(object):  # 0-indexed.
        def __init__(self, n):
            self.__bit = [0]*(n+1)

        def add(self, i, val):
            i += 1
            while i < len(self.__bit):
                self.__bit[i] += val
                i += (i & -i)

        def query(self, i):
            i += 1
            ret = 0
            while i > 0:
                ret += self.__bit[i]
                i -= (i & -i)
            return ret

    def update(i, d):
        if d == +1:
            sl.add(i)
            if len(sl) == 1:
                bit1.add(n, +1)
                bit2.add(n, +n)
        curr = sl.index(i)
        prv, nxt = (curr-1)%len(sl), (curr+1)%len(sl)
        if len(sl) != 1:
            l = (sl[nxt]-sl[prv]-1)%n+1
            bit1.add(l, d*(-1))
            bit2.add(l, d*(-l))
            l = (sl[curr]-sl[prv])%n
            bit1.add(l, d*(+1))
            bit2.add(l, d*(+l))
            l = (sl[nxt]-sl[curr])%n
            bit1.add(l, d*(+1))
            bit2.add(l, d*(+l))
        if d == -1:
            if len(sl) == 1:
                bit1.add(n, -1)
                bit2.add(n, -n)
            sl.pop(curr)

    n = len(colors)
    sl = SortedList()
    bit1, bit2 = BIT(n+1), BIT(n+1)
    for i in xrange(n):
        if colors[i] == colors[(i+1)%n]:
            update(i, +1)
    result = []
    for q in queries:
        if q[0] == 1:
            l = q[1]
            result.append((bit2.query(n)-bit2.query(l-1))-
                          (l-1)*(bit1.query(n)-bit1.query(l-1)) if sl else n)
            continue
        _, i, c = q
        if colors[i] == c:
            continue      
        colors[i] = c          
        update((i-1)%n, +1 if colors[i] == colors[(i-1)%n] else -1) 
        update(i, +1 if colors[i] == colors[(i+1)%n] else -1)
    return result


