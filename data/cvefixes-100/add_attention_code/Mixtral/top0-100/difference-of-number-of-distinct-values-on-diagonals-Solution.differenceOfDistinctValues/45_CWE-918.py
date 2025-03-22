def render_downloaded_books(page, order, user_id):
    if current_user.role_admin():
        user_id = int(user_id)
    else:
        user_id = current_user.id
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD):
        if current_user.show_detail_random():
            random = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                .order_by(func.random()).limit(config.config_random_books)
        else:
            random = false()

        entries, __, pagination = calibre_db.fill_indexpage(page,
                                                            0,
                                                            db.Books,
                                                            ub.Downloads.user_id == user_id,
                                                            order[0],
                                                            False, 0,
                                                            db.books_series_link,
                                                            db.Books.id == db.books_series_link.c.book,
                                                            db.Series,
                                                            ub.Downloads, db.Books.id == ub.Downloads.book_id)
        for book in entries:
            if not calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                             .filter(db.Books.id == book.id).first():
                ub.delete_download(book.id)
        user = ub.session.query(ub.User).filter(ub.User.id == user_id).first()
        return render_title_template('index.html',
                                     random=random,
                                     entries=entries,
                                     pagination=pagination,
                                     id=user_id,
                                     title=_(u"Downloaded books by %(user)s",user=user.name),
                                     page="download",
                                     order=order[1])
    else:
        abort(404)

def differenceOfDistinctValues(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: List[List[int]]
    """
    def update(i, j):
        lookup = set()
        for k in xrange(min(len(grid)-i, len(grid[0])-j)):
            result[i+k][j+k] = len(lookup)
            lookup.add(grid[i+k][j+k])
        lookup.clear()
        for k in reversed(xrange(min(len(grid)-i, len(grid[0])-j))):
            result[i+k][j+k] = abs(result[i+k][j+k]-len(lookup))
            lookup.add(grid[i+k][j+k])

    result = [[0]*len(grid[0]) for _ in xrange(len(grid))]
    for j in xrange(len(grid[0])):
        update(0, j)
    for i in xrange(1, len(grid)):
        update(i, 0)
    return result


