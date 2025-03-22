def render_archived_books(page, sort_param):
    order = sort_param[0] or []
    archived_books = (
        ub.session.query(ub.ArchivedBook)
        .filter(ub.ArchivedBook.user_id == int(current_user.id))
        .filter(ub.ArchivedBook.is_archived == True)
        .all()
    )
    archived_book_ids = [archived_book.book_id for archived_book in archived_books]

    archived_filter = db.Books.id.in_(archived_book_ids)

    entries, random, pagination = calibre_db.fill_indexpage_with_archived_books(page, db.Books,
                                                                                0,
                                                                                archived_filter,
                                                                                order,
                                                                                True,
                                                                                False, 0)

    name = _(u'Archived Books') + ' (' + str(len(archived_book_ids)) + ')'
    pagename = "archived"
    return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                 title=name, page=pagename, order=sort_param[1])

def getMinSwaps(self, num, k):
    """
    :type num: str
    :type k: int
    :rtype: int
    """
    def next_permutation(nums, begin, end):
        def reverse(nums, begin, end):
            left, right = begin, end-1
            while left < right:
                nums[left], nums[right] = nums[right], nums[left]
                left += 1
                right -= 1

        k, l = begin-1, begin
        for i in reversed(xrange(begin, end-1)):
            if nums[i] < nums[i+1]:
                k = i
                break
        else:
            reverse(nums, begin, end)
            return False
        for i in reversed(xrange(k+1, end)):
            if nums[i] > nums[k]:
                l = i
                break
        nums[k], nums[l] = nums[l], nums[k]
        reverse(nums, k+1, end)
        return True
    
    new_num = list(num)
    while k:
        next_permutation(new_num, 0, len(new_num))
        k -= 1
    result = 0
    for i in xrange(len(new_num)):
        if new_num[i] == num[i]:
            continue
        #   // greedily move the one with the least cost from new_num to num without missing optimal cost
        for j in xrange(i+1, len(new_num)):
            if new_num[j] == num[i]:
                break
        result += j-i
        for j in reversed(xrange(i+1, j+1)):
            new_num[j], new_num[j-1] = new_num[j-1], new_num[j]
    return result


