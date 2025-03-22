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


