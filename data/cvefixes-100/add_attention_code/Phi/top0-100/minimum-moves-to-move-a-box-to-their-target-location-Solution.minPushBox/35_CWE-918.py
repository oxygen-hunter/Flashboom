def ratings_list():
    if current_user.check_visibility(constants.SIDEBAR_RATING):
        if current_user.get_view_property('ratings', 'dir') == 'desc':
            order = db.Ratings.rating.desc()
            order_no = 0
        else:
            order = db.Ratings.rating.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Ratings, func.count('books_ratings_link.book').label('count'),
                                   (db.Ratings.rating / 2).label('name')) \
            .join(db.books_ratings_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_ratings_link.rating')).order_by(order).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=list(),
                                     title=_(u"Ratings list"), page="ratingslist", data="ratings", order=order_no)
    else:
        abort(404)

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


