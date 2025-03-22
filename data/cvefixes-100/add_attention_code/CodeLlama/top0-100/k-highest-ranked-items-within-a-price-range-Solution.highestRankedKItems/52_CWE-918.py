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

def highestRankedKItems(self, grid, pricing, start, k):
    """
    :type grid: List[List[int]]
    :type pricing: List[int]
    :type start: List[int]
    :type k: int
    :rtype: List[List[int]]
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    def nth_element(nums, n, left=0, compare=lambda a, b: a < b):
        def tri_partition(nums, left, right, target, compare):
            mid = left
            while mid <= right:
                if nums[mid] == target:
                    mid += 1
                elif compare(nums[mid], target):
                    nums[left], nums[mid] = nums[mid], nums[left]
                    left += 1
                    mid += 1
                else:
                    nums[mid], nums[right] = nums[right], nums[mid]
                    right -= 1
            return left, right

        right = len(nums)-1
        while left <= right:
            pivot_idx = random.randint(left, right)
            pivot_left, pivot_right = tri_partition(nums, left, right, nums[pivot_idx], compare)
            if pivot_left <= n <= pivot_right:
                return
            elif pivot_left > n:
                right = pivot_left-1
            else:  # pivot_right < n.
                left = pivot_right+1

    def get_val(x):
        return (lookup[x[0]][x[1]], grid[x[0]][x[1]], x[0], x[1])

    result = []
    q = [start]
    lookup = [[-1]*len(grid[0]) for _ in xrange(len(grid))]
    d = lookup[start[0]][start[1]] = 0
    while q:
        if len(result) >= k:
            if len(result) > k:
                nth_element(result, k-1, compare=lambda a, b: get_val(a) < get_val(b))
                result = result[:k]
            break
        new_q = []
        for r, c in q:
            if pricing[0] <= grid[r][c] <= pricing[1]:
                result.append([r, c])
            for dr, dc in directions:
                nr, nc = r+dr, c+dc
                if not (0 <= nr < len(grid) and 0 <= nc < len(grid[0]) and grid[nr][nc] and lookup[nr][nc] == -1):
                    continue
                lookup[nr][nc] = d+1
                new_q.append((nr, nc))
        q = new_q
        d += 1
    result.sort(key=lambda x: get_val(x))
    return result


