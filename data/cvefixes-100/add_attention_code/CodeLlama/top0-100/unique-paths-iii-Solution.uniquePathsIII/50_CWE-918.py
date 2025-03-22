def render_prepare_search_form(cc):
    # prepare data for search-form
    tags = calibre_db.session.query(db.Tags)\
        .join(db.books_tags_link)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(text('books_tags_link.tag'))\
        .order_by(db.Tags.name).all()
    series = calibre_db.session.query(db.Series)\
        .join(db.books_series_link)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(text('books_series_link.series'))\
        .order_by(db.Series.name)\
        .filter(calibre_db.common_filters()).all()
    shelves = ub.session.query(ub.Shelf)\
        .filter(or_(ub.Shelf.is_public == 1, ub.Shelf.user_id == int(current_user.id)))\
        .order_by(ub.Shelf.name).all()
    extensions = calibre_db.session.query(db.Data)\
        .join(db.Books)\
        .filter(calibre_db.common_filters()) \
        .group_by(db.Data.format)\
        .order_by(db.Data.format).all()
    if current_user.filter_language() == u"all":
        languages = calibre_db.speaking_language()
    else:
        languages = None
    return render_title_template('search_form.html', tags=tags, languages=languages, extensions=extensions,
                                 series=series,shelves=shelves, title=_(u"Advanced Search"), cc=cc, page="advsearch")

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


