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

def searchRange(self, nums, target):
    """
    :type nums: List[int]
    :type target: int
    :rtype: List[int]
    """
    def binarySearch(n, check):  # usually use
        left, right = 0, n-1  # search in [0, n-1], return n if not found
        while left <= right:
            mid = left + (right-left)//2
            if check(mid):
                right = mid-1
            else:
                left = mid+1
        return left  # or return right+1

    def binarySearch2(n, check):  # frequently use
        left, right = 0, n  # search in [0, n), return n if not found
        while left < right:
            mid = left + (right-left)//2
            if check(mid):
                right = mid
            else:
                left = mid+1
        return left  # or return right

    def binarySearch3(n, check):  # never use
        left, right = -1, n-1  # search in (-1, n-1], return n if not found
        while left < right:
            mid = right - (right-left)//2
            if check(mid):
                right = mid-1
            else:
                left = mid
        return left+1  # or return right+1

    def binarySearch4(n, check):  # sometimes use
        left, right = -1, n  # search in (-1, n), return n if not found
        while right-left >= 2:
            mid = left + (right-left)//2
            if check(mid):
                right = mid
            else:
                left = mid
        return left+1  # or return right

    # Find the first idx where nums[idx] >= target
    left = binarySearch(len(nums), lambda i: nums[i] >= target)
    if left == len(nums) or nums[left] != target:
        return [-1, -1]
    # Find the first idx where nums[idx] > target
    right = binarySearch(len(nums), lambda i: nums[i] > target)
    return [left, right-1]


