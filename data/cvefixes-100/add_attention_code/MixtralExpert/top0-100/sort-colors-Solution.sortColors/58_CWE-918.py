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

def sortColors(self, nums):
    """
    :type nums: List[int]
    :rtype: void Do not return anything, modify nums in-place instead.
    """
    def triPartition(nums, target):
        i, left, right = 0, 0, len(nums)-1
        while i <= right:
            if nums[i] > target:
                nums[i], nums[right] = nums[right], nums[i]
                right -= 1
            else:
                if nums[i] < target:
                    nums[left], nums[i] = nums[i], nums[left]
                    left += 1
                i += 1

    triPartition(nums, 1)


