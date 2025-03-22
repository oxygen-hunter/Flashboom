def read_book(book_id, book_format):
    book = calibre_db.get_filtered_book(book_id)
    book.ordered_authors = calibre_db.order_authors([book], False)

    if not book:
        flash(_(u"Oops! Selected book title is unavailable. File does not exist or is not accessible"), category="error")
        log.debug(u"Oops! Selected book title is unavailable. File does not exist or is not accessible")
        return redirect(url_for("web.index"))

    # check if book has a bookmark
    bookmark = None
    if current_user.is_authenticated:
        bookmark = ub.session.query(ub.Bookmark).filter(and_(ub.Bookmark.user_id == int(current_user.id),
                                                             ub.Bookmark.book_id == book_id,
                                                             ub.Bookmark.format == book_format.upper())).first()
    if book_format.lower() == "epub":
        log.debug(u"Start epub reader for %d", book_id)
        return render_title_template('read.html', bookid=book_id, title=book.title, bookmark=bookmark)
    elif book_format.lower() == "pdf":
        log.debug(u"Start pdf reader for %d", book_id)
        return render_title_template('readpdf.html', pdffile=book_id, title=book.title)
    elif book_format.lower() == "txt":
        log.debug(u"Start txt reader for %d", book_id)
        return render_title_template('readtxt.html', txtfile=book_id, title=book.title)
    elif book_format.lower() == "djvu":
        log.debug(u"Start djvu reader for %d", book_id)
        return render_title_template('readdjvu.html', djvufile=book_id, title=book.title)
    else:
        for fileExt in constants.EXTENSIONS_AUDIO:
            if book_format.lower() == fileExt:
                entries = calibre_db.get_filtered_book(book_id)
                log.debug(u"Start mp3 listening for %d", book_id)
                return render_title_template('listenmp3.html', mp3file=book_id, audioformat=book_format.lower(),
                                             entry=entries, bookmark=bookmark)
        for fileExt in ["cbr", "cbt", "cbz"]:
            if book_format.lower() == fileExt:
                all_name = str(book_id)
                title = book.title
                if len(book.series):
                    title = title + " - " + book.series[0].name
                    if book.series_index:
                        title = title + " #" + '{0:.2f}'.format(book.series_index).rstrip('0').rstrip('.')
                log.debug(u"Start comic reader for %d", book_id)
                return render_title_template('readcbr.html', comicfile=all_name, title=title,
                                             extension=fileExt)
        log.debug(u"Oops! Selected book title is unavailable. File does not exist or is not accessible")
        flash(_(u"Oops! Selected book title is unavailable. File does not exist or is not accessible"), category="error")
        return redirect(url_for("web.index"))

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


