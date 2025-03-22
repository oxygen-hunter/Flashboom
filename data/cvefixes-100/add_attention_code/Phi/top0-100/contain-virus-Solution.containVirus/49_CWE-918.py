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

def containVirus(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    directions = [(0, 1), (0, -1), (-1, 0), (1, 0)]

    def dfs(grid, r, c, lookup, regions, frontiers, perimeters):
        if (r, c) in lookup:
            return
        lookup.add((r, c))
        regions[-1].add((r, c))
        for d in directions:
            nr, nc = r+d[0], c+d[1]
            if not (0 <= nr < len(grid) and \
                    0 <= nc < len(grid[r])):
                continue
            if grid[nr][nc] == 1:
                dfs(grid, nr, nc, lookup, regions, frontiers, perimeters)
            elif grid[nr][nc] == 0:
                frontiers[-1].add((nr, nc))
                perimeters[-1] += 1

    result = 0
    while True:
        lookup, regions, frontiers, perimeters = set(), [], [], []
        for r, row in enumerate(grid):
            for c, val in enumerate(row):
                if val == 1 and (r, c) not in lookup:
                    regions.append(set())
                    frontiers.append(set())
                    perimeters.append(0)
                    dfs(grid, r, c, lookup, regions, frontiers, perimeters)

        if not regions: break

        triage_idx = frontiers.index(max(frontiers, key = len))
        for i, region in enumerate(regions):
            if i == triage_idx:
                result += perimeters[i]
                for r, c in region:
                    grid[r][c] = -1
                continue
            for r, c in region:
                for d in directions:
                    nr, nc = r+d[0], c+d[1]
                    if not (0 <= nr < len(grid) and \
                            0 <= nc < len(grid[r])):
                        continue
                    if grid[nr][nc] == 0:
                        grid[nr][nc] = 1

    return result



