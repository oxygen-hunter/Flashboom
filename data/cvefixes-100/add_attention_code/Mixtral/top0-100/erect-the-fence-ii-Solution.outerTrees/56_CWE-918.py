def series_list():
    if current_user.check_visibility(constants.SIDEBAR_SERIES):
        if current_user.get_view_property('series', 'dir') == 'desc':
            order = db.Series.sort.desc()
            order_no = 0
        else:
            order = db.Series.sort.asc()
            order_no = 1
        if current_user.get_view_property('series', 'series_view') == 'list':
            entries = calibre_db.session.query(db.Series, func.count('books_series_link.book').label('count')) \
                .join(db.books_series_link).join(db.Books).filter(calibre_db.common_filters()) \
                .group_by(text('books_series_link.series')).order_by(order).all()
            charlist = calibre_db.session.query(func.upper(func.substr(db.Series.sort, 1, 1)).label('char')) \
                .join(db.books_series_link).join(db.Books).filter(calibre_db.common_filters()) \
                .group_by(func.upper(func.substr(db.Series.sort, 1, 1))).all()
            return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                         title=_(u"Series"), page="serieslist", data="series", order=order_no)
        else:
            entries = calibre_db.session.query(db.Books, func.count('books_series_link').label('count'),
                                               func.max(db.Books.series_index), db.Books.id) \
                .join(db.books_series_link).join(db.Series).filter(calibre_db.common_filters())\
                .group_by(text('books_series_link.series')).order_by(order).all()
            charlist = calibre_db.session.query(func.upper(func.substr(db.Series.sort, 1, 1)).label('char')) \
                .join(db.books_series_link).join(db.Books).filter(calibre_db.common_filters()) \
                .group_by(func.upper(func.substr(db.Series.sort, 1, 1))).all()

            return render_title_template('grid.html', entries=entries, folder='web.books_list', charlist=charlist,
                                         title=_(u"Series"), page="serieslist", data="series", bodyClass="grid-view",
                                         order=order_no)
    else:
        abort(404)

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


