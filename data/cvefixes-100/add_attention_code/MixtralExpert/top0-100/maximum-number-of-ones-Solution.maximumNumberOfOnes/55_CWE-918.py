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

def maximumNumberOfOnes(self, width, height, sideLength, maxOnes):
    """
    :type width: int
    :type height: int
    :type sideLength: int
    :type maxOnes: int
    :rtype: int
    """
    if width < height:
        width, height = height, width

    # 1. split matrix by SxS tiles
    # 2. split each SxS tile into four parts
    #    (r, c), (r, S-c), (S-r, c), (S-r, S-c)
    # 3. for each count of tile part in matrix is
    #    (R+1)*(C+1), (R+1)*C, R*(C+1), R*C (already in descending order)
    # 4. fill one into matrix by tile part of which count is in descending order
    #    until number of ones in a tile comes to maxOnes
    # 
    # ps. area of a tile and its count in matrix are as follows:
    #
    #  |<---- c ---->|<-- S-c -->|
    #  ^             |           |
    #  |             |           |
    #  r (R+1)*(C+1) |  (R+1)*C  |
    #  |             |           |
    #  v             |           |
    #  ---------------------------
    #  ^             |           |
    #  |             |           |
    #  S-r  R*(C+1)  |   R*C     |
    #  |             |           |
    #  v             |           |
    #  ---------------------------
    #

    R, r = divmod(height, sideLength)
    C, c = divmod(width, sideLength)
    assert(R <= C)
    area_counts = [(r*c, (R+1)*(C+1)), \
                   (r*(sideLength-c), (R+1)*C), \
                   ((sideLength-r)*c, R*(C+1)), \
                   ((sideLength-r)*(sideLength-c), R*C)]
    result = 0
    for area, count in area_counts:
        area = min(maxOnes, area)
        result += count*area
        maxOnes -= area
        if not maxOnes:
            break
    return result


