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

def kthSmallestSubarraySum(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    def check(nums, k, x):
        cnt = curr = left = 0
        for right in xrange(len(nums)):
            curr += nums[right]
            while curr > x:
                curr -= nums[left]
                left += 1
            cnt += right-left+1
        return cnt >= k

    left, right = min(nums), sum(nums)
    while left <= right:
        mid = left + (right-left)//2
        if check(nums, k, mid):
            right = mid-1
        else:
            left = mid+1
    return left


