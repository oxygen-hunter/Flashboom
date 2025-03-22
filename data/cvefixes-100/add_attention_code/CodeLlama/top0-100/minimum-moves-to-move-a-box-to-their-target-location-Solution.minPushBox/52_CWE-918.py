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

def minPushBox(self, grid):
    """
    :type grid: List[List[str]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    def dot(a, b):
        return a[0]*b[0]+a[1]*b[1]

    def can_reach(grid, b, p, t):
        closer, detour = [p], []
        lookup = set([b])
        while closer or detour:
            if not closer:
                closer, detour = detour, closer
            p = closer.pop()
            if p == t:
                return True
            if p in lookup:
                continue
            lookup.add(p)
            for dx, dy in directions:
                np = (p[0]+dx, p[1]+dy)
                if not (0 <= np[0] < len(grid) and 0 <= np[1] < len(grid[0]) and
                   grid[np[0]][np[1]] != '#' and np not in lookup):
                    continue
                (closer if dot((dx, dy), (t[0]-p[0], t[1]-p[1])) > 0 else detour).append(np)
        return False

    def g(a, b):
        return abs(a[0]-b[0])+abs(a[1]-b[1])
    
    def a_star(grid, b, p, t):
        f, dh = g(b, t), 2
        closer, detour = [(b, p)], []
        lookup = set()
        while closer or detour:
            if not closer:
                f += dh
                closer, detour = detour, closer
            b, p = closer.pop()
            if b == t:
                return f
            if (b, p) in lookup:
                continue
            lookup.add((b, p))
            for dx, dy in directions:
                nb, np = (b[0]+dx, b[1]+dy), (b[0]-dx, b[1]-dy)
                if not (0 <= nb[0] < len(grid) and 0 <= nb[1] < len(grid[0]) and
                        0 <= np[0] < len(grid) and 0 <= np[1] < len(grid[0]) and
                        grid[nb[0]][nb[1]] != '#' and grid[np[0]][np[1]] != '#' and
                        (nb, b) not in lookup and can_reach(grid, b, p, np)):
                    continue
                (closer if dot((dx, dy), (t[0]-b[0], t[1]-b[1])) > 0 else detour).append((nb, b))
        return -1
    
    b, p, t = None, None, None
    for i in xrange(len(grid)):
        for j in xrange(len(grid[0])):
            if grid[i][j] == 'B':
                b = (i, j)
            elif grid[i][j] == 'S':
                p = (i, j)
            elif grid[i][j] == 'T':
                t = (i, j)
    return a_star(grid, b, p, t)


