def set_bookmark(book_id, book_format):
    bookmark_key = request.form["bookmark"]
    ub.session.query(ub.Bookmark).filter(and_(ub.Bookmark.user_id == int(current_user.id),
                                              ub.Bookmark.book_id == book_id,
                                              ub.Bookmark.format == book_format)).delete()
    if not bookmark_key:
        ub.session_commit()
        return "", 204

    lbookmark = ub.Bookmark(user_id=current_user.id,
                            book_id=book_id,
                            format=book_format,
                            bookmark_key=bookmark_key)
    ub.session.merge(lbookmark)
    ub.session_commit("Bookmark for user {} in book {} created".format(current_user.id, book_id))
    return "", 201

def maxSubsequence(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: List[int]
    """
    def nth_element(nums, n, compare=lambda a, b: a < b):
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

        left, right = 0, len(nums)-1
        while left <= right:
            pivot_idx = random.randint(left, right)
            pivot_left, pivot_right = tri_partition(nums, left, right, nums[pivot_idx], compare)
            if pivot_left <= n <= pivot_right:
                return
            elif pivot_left > n:
                right = pivot_left-1
            else:  # pivot_right < n.
                left = pivot_right+1

    partition = nums[:]
    nth_element(partition, k-1, compare=lambda a, b: a > b)
    cnt = sum(partition[i] == partition[k-1] for i in xrange(k))
    result = []
    for x in nums:
        if x > partition[k-1]:
            result.append(x)
        elif x == partition[k-1] and cnt > 0:
            cnt -= 1
            result.append(x)
    return result


