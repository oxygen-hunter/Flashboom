def profile():
    languages = calibre_db.speaking_language()
    translations = babel.list_translations() + [LC('en')]
    kobo_support = feature_support['kobo'] and config.config_kobo_sync
    if feature_support['oauth'] and config.config_login_type == 2:
        oauth_status = get_oauth_status()
        local_oauth_check = oauth_check
    else:
        oauth_status = None
        local_oauth_check = {}

    if request.method == "POST":
        change_profile(kobo_support, local_oauth_check, oauth_status, translations, languages)
    return render_title_template("user_edit.html",
                                 translations=translations,
                                 profile=1,
                                 languages=languages,
                                 content=current_user,
                                 kobo_support=kobo_support,
                                 title=_(u"%(name)s's profile", name=current_user.name),
                                 page="me",
                                 registered_oauth=local_oauth_check,
                                 oauth_status=oauth_status)

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



