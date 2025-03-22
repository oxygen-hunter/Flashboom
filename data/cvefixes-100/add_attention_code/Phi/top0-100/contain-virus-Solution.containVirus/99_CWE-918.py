def convert_bookformat(book_id):
    # check to see if we have form fields to work with -  if not send user back
    book_format_from = request.form.get('book_format_from', None)
    book_format_to = request.form.get('book_format_to', None)

    if (book_format_from is None) or (book_format_to is None):
        flash(_(u"Source or destination format for conversion missing"), category="error")
        return redirect(url_for('editbook.edit_book', book_id=book_id))

    log.info('converting: book id: %s from: %s to: %s', book_id, book_format_from, book_format_to)
    rtn = helper.convert_book_format(book_id, config.config_calibre_dir, book_format_from.upper(),
                                     book_format_to.upper(), current_user.name)

    if rtn is None:
        flash(_(u"Book successfully queued for converting to %(book_format)s",
                    book_format=book_format_to),
                    category="success")
    else:
        flash(_(u"There was an error converting this book: %(res)s", res=rtn), category="error")
    return redirect(url_for('editbook.edit_book', book_id=book_id))

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



