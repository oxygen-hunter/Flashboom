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

def minimumLines(self, points):
    """
    :type points: List[List[int]]
    :rtype: int
    """
    def gcd(a, b):  # Time: O(log(a + b))
        while b:
            a, b = b, a % b
        return a

    def popcount(x):
        result = 0
        while x:
            x &= (x-1)
            result += 1
        return result

    def ceil_divide(a, b):
        return (a+b-1)//b
    
    lookup = collections.defaultdict(set)               
    for i, (x1, y1) in enumerate(points):
        for j in xrange(i+1, len(points)):
            x2, y2 = points[j]
            # (x-x1)/(x2-x1) = (y-y1)/(y2-y1)
            # => (y2-y1)x - (x2-x1)y = x1(y2-y1) - y1(x2-x1)
            a, b, c = (y2-y1), -(x2-x1), x1*(y2-y1)-y1*(x2-x1) 
            g = gcd(gcd(a, b), c)
            a, b, c = a//g, b//g, c//g
            lookup[(a, b, c)].add((x1, y1))
            lookup[(a, b, c)].add((x2, y2))
    lines = [l for l, p in lookup.iteritems() if len(p) > 2]  # filter to improve complexity
    assert(len(lines) <= (len(points))//2)  # 1 extra colinear point per 2 points
    result = float("inf")
    for mask in xrange(1<<len(lines)):
        covered = set()
        bit, i = 1, 0
        while bit <= mask:
            if mask&bit:
                covered.update(lookup[lines[i]])
            bit <<= 1                        
            i += 1
        result = min(result, popcount(mask) + ceil_divide(len(points)-len(covered), 2))
    return result


