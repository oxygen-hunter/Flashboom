def render_prepare_search_form(cc):
    # prepare data for search-form
    tags = calibre_db.session.query(db.Tags)\
        .join(db.books_tags_link)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(text('books_tags_link.tag'))\
        .order_by(db.Tags.name).all()
    series = calibre_db.session.query(db.Series)\
        .join(db.books_series_link)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(text('books_series_link.series'))\
        .order_by(db.Series.name)\
        .filter(calibre_db.common_filters()).all()
    shelves = ub.session.query(ub.Shelf)\
        .filter(or_(ub.Shelf.is_public == 1, ub.Shelf.user_id == int(current_user.id)))\
        .order_by(ub.Shelf.name).all()
    extensions = calibre_db.session.query(db.Data)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(db.Data.format)\
        .order_by(db.Data.format).all()
    if current_user.filter_language() == u"all":
        languages = calibre_db.speaking_language()
    else:
        languages = None
    return render_title_template('search_form.html', tags=tags, languages=languages, extensions=extensions,
                                 series=series,shelves=shelves, title=_(u"Advanced Search"), cc=cc, page="advsearch")

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


