def render_read_books(page, are_read, as_xml=False, order=None):
    sort_param = order[0] if order else []
    if not config.config_read_column:
        if are_read:
            db_filter = and_(ub.ReadBook.user_id == int(current_user.id),
                             ub.ReadBook.read_status == ub.ReadBook.STATUS_FINISHED)
        else:
            db_filter = coalesce(ub.ReadBook.read_status, 0) != ub.ReadBook.STATUS_FINISHED
        entries, random, pagination = calibre_db.fill_indexpage(page, 0,
                                                                db.Books,
                                                                db_filter,
                                                                sort_param,
                                                                False, 0,
                                                                db.books_series_link,
                                                                db.Books.id == db.books_series_link.c.book,
                                                                db.Series,
                                                                ub.ReadBook, db.Books.id == ub.ReadBook.book_id)
    else:
        try:
            if are_read:
                db_filter = db.cc_classes[config.config_read_column].value == True
            else:
                db_filter = coalesce(db.cc_classes[config.config_read_column].value, False) != True
            entries, random, pagination = calibre_db.fill_indexpage(page, 0,
                                                                    db.Books,
                                                                    db_filter,
                                                                    sort_param,
                                                                    False, 0,
                                                                    db.books_series_link,
                                                                    db.Books.id == db.books_series_link.c.book,
                                                                    db.Series,
                                                                    db.cc_classes[config.config_read_column])
        except (KeyError, AttributeError):
            log.error("Custom Column No.%d is not existing in calibre database", config.config_read_column)
            if not as_xml:
                flash(_("Custom Column No.%(column)d is not existing in calibre database",
                        column=config.config_read_column),
                      category="error")
                return redirect(url_for("web.index"))
            return [] # ToDo: Handle error Case for opds

    if as_xml:
        return entries, pagination
    else:
        if are_read:
            name = _(u'Read Books') + ' (' + str(pagination.total_count) + ')'
            pagename = "read"
        else:
            name = _(u'Unread Books') + ' (' + str(pagination.total_count) + ')'
            pagename = "unread"
        return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                     title=name, page=pagename, order=order[1])

def largestMagicSquare(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    def get_sum(prefix, a, b):
        return prefix[b+1]-prefix[a]

    def check(grid, prefix_row, prefix_col, l, i, j):
        diag, anti_diag = 0, 0
        for d in xrange(l):
            diag += grid[i+d][j+d]
            anti_diag += grid[i+d][j+l-1-d]
        if diag != anti_diag:
            return False
        for ni in xrange(i, i+l):
            if diag != get_sum(prefix_row[ni], j, j+l-1):
                return False
        for nj in xrange(j, j+l):
            if diag != get_sum(prefix_col[nj], i, i+l-1):
                return False  
        return True

    prefix_row = [[0]*(len(grid[0])+1) for _ in xrange(len(grid))]
    prefix_col = [[0]*(len(grid)+1) for _ in xrange(len(grid[0]))]
    for i in xrange(len(grid)):
        for j in xrange(len(grid[0])):
            prefix_row[i][j+1] = prefix_row[i][j] + grid[i][j]
            prefix_col[j][i+1] = prefix_col[j][i] + grid[i][j]
    for l in reversed(xrange(1, min(len(grid), len(grid[0]))+1)):
        for i in xrange(len(grid)-(l-1)):
            for j in xrange(len(grid[0])-(l-1)):
                if check(grid, prefix_row, prefix_col, l, i, j):
                    return l
    return 1


