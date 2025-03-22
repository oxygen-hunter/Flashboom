def render_hot_books(page, order):
    if current_user.check_visibility(constants.SIDEBAR_HOT):
        if order[1] not in ['hotasc', 'hotdesc']:
        # Unary expression comparsion only working (for this expression) in sqlalchemy 1.4+
        #if not (order[0][0].compare(func.count(ub.Downloads.book_id).desc()) or
        #        order[0][0].compare(func.count(ub.Downloads.book_id).asc())):
            order = [func.count(ub.Downloads.book_id).desc()], 'hotdesc'
        if current_user.show_detail_random():
            random = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                .order_by(func.random()).limit(config.config_random_books)
        else:
            random = false()
        off = int(int(config.config_books_per_page) * (page - 1))
        all_books = ub.session.query(ub.Downloads, func.count(ub.Downloads.book_id))\
            .order_by(*order[0]).group_by(ub.Downloads.book_id)
        hot_books = all_books.offset(off).limit(config.config_books_per_page)
        entries = list()
        for book in hot_books:
            downloadBook = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()).filter(
                db.Books.id == book.Downloads.book_id).first()
            if downloadBook:
                entries.append(downloadBook)
            else:
                ub.delete_download(book.Downloads.book_id)
        numBooks = entries.__len__()
        pagination = Pagination(page, config.config_books_per_page, numBooks)
        return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                     title=_(u"Hot Books (Most Downloaded)"), page="hot", order=order[1])
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


