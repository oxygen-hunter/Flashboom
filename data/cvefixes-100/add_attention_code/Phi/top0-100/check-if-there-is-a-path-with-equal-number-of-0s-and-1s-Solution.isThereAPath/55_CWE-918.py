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

def isThereAPath(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: bool
    """
    if (len(grid)+len(grid[0])-1)%2:
        return False
    dp_left = [[float("inf")]*(len(grid[0])+1) for _ in xrange(2)]
    dp_left[0][1] = dp_left[1][0] = 0
    dp_right = [[float("-inf")]*(len(grid[0])+1) for _ in xrange(2)]
    dp_right[0][1] = dp_right[1][0] = 0
    for i in xrange(len(grid)):
        for j in xrange(len(grid[0])):
            dp_left[(i+1)%2][j+1] = min(dp_left[i%2][j+1], dp_left[(i+1)%2][j])+grid[i][j]
            dp_right[(i+1)%2][j+1] = max(dp_right[i%2][j+1], dp_right[(i+1)%2][j])+grid[i][j]
    return dp_left[len(grid)%2][-1] <= (len(grid)+len(grid[0])-1)//2 <= dp_right[len(grid)%2][-1]


