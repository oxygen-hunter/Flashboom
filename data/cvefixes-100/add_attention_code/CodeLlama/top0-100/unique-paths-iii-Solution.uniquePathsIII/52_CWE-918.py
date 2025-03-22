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

def uniquePathsIII(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    
    def index(grid, r, c):
        return 1 << (r*len(grid[0])+c)

    def dp(grid, src, dst, todo, lookup):
        if src == dst:
            return int(todo == 0)
        key = (src, todo)
        if key in lookup:
            return lookup[key]

        result = 0
        for d in directions:
            r, c = src[0]+d[0], src[1]+d[1]
            if 0 <= r < len(grid) and 0 <= c < len(grid[0]) and \
               grid[r][c] % 2 == 0 and \
               todo & index(grid, r, c):
                result += dp(grid, (r, c), dst, todo ^ index(grid, r, c), lookup)

        lookup[key] = result
        return lookup[key]

    todo = 0
    src, dst = None, None
    for r, row in enumerate(grid):
        for c, val in enumerate(row):
            if val % 2 == 0:
                todo |= index(grid, r, c)
            if val == 1:
                src = (r, c)
            elif val == 2:
                dst = (r, c)
    return dp(grid, src, dst, todo, {})


