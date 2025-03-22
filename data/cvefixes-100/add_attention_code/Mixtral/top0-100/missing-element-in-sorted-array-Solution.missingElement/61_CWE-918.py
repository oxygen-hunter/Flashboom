def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

def missingElement(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    def missing_count(nums, x):
        return (nums[x]-nums[0]+1)-(x-0+1)

    def check(nums, k, x):
        return k > missing_count(nums, x)

    left, right = 0, len(nums)-1
    while left <= right:  # find the largest right s.t. k > missingCount(nums, x)
        mid = left + (right-left)//2
        if not check(nums, k, mid):
            right = mid-1
        else:
            left = mid+1
    assert(check(nums, k, right))
    return nums[right] + (k-missing_count(nums, right))


