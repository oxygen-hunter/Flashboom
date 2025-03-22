def show_book(book_id):
    entries = calibre_db.get_book_read_archived(book_id, config.config_read_column, allow_show_archived=True)
    if entries:
        read_book = entries[1]
        archived_book = entries[2]
        entry = entries[0]
        entry.read_status = read_book == ub.ReadBook.STATUS_FINISHED
        entry.is_archived = archived_book
        for index in range(0, len(entry.languages)):
            entry.languages[index].language_name = isoLanguages.get_language_name(get_locale(), entry.languages[
                index].lang_code)
        cc = get_cc_columns(filter_config_custom_read=True)
        book_in_shelfs = []
        shelfs = ub.session.query(ub.BookShelf).filter(ub.BookShelf.book_id == book_id).all()
        for sh in shelfs:
            book_in_shelfs.append(sh.shelf)

        entry.tags = sort(entry.tags, key=lambda tag: tag.name)

        entry.ordered_authors = calibre_db.order_authors([entry])

        entry.kindle_list = check_send_to_kindle(entry)
        entry.reader_list = check_read_formats(entry)

        entry.audioentries = []
        for media_format in entry.data:
            if media_format.format.lower() in constants.EXTENSIONS_AUDIO:
                entry.audioentries.append(media_format.format.lower())

        return render_title_template('detail.html',
                                     entry=entry,
                                     cc=cc,
                                     is_xhr=request.headers.get('X-Requested-With')=='XMLHttpRequest',
                                     title=entry.title,
                                     books_shelfs=book_in_shelfs,
                                     page="book")
    else:
        log.debug(u"Oops! Selected book title is unavailable. File does not exist or is not accessible")
        flash(_(u"Oops! Selected book title is unavailable. File does not exist or is not accessible"),
              category="error")
        return redirect(url_for("web.index"))

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


