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

def outerTrees(self, trees):
    """
    :type trees: List[List[int]]
    :rtype: List[float]
    """
    def dist(a, b):
        return ((a[0]-b[0])**2 + (a[1]-b[1])**2)**0.5

    def inside(c, p):
        return dist(c[0], p) < c[1]+EPS

    def circle_center(bx, by, cx, cy):
        B = bx*bx + by*by
        C = cx*cx + cy*cy
        D = bx*cy - by*cx
        return [float(cy*B - by*C)/(2*D),
                float(bx*C - cx*B)/(2*D)]

    def circle_from_2_points(A, B):
        C = [(A[0]+B[0])/2.0, (A[1]+B[1])/2.0]
        return [C, dist(A, B)/2.0]

    def circle_from_3_points(A, B, C):
        I = circle_center(B[0]-A[0], B[1]-A[1],
                          C[0]-A[0], C[1]-A[1])
        I[0] += A[0]
        I[1] += A[1]
        return [I, dist(I, A)]

    def trivial(boundaries):  # circumscribed circle
        if not boundaries:
            return None
        if len(boundaries) == 1:
            return [boundaries[0], 0.0]
        if len(boundaries) == 2:
            return circle_from_2_points(boundaries[0], boundaries[1])
        return circle_from_3_points(boundaries[0], boundaries[1], boundaries[2])

    def Welzl(points, boundaries, curr):
        if curr == len(points) or len(boundaries) == 3:
            return trivial(boundaries)
        result = Welzl(points, boundaries, curr+1)
        if result is not None and inside(result, points[curr]):
            return result
        boundaries.append(points[curr])
        result = Welzl(points, boundaries, curr+1)
        boundaries.pop()
        return result

    EPS = 1e-5
    random.seed(0)
    random.shuffle(trees)
    result = Welzl(trees, [], 0)
    return result[0][0], result[0][1], result[1]


