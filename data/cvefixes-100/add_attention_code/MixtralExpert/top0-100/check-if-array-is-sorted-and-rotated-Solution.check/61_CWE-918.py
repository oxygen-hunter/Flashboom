def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

def check(self, nums):
    """
    :type nums: List[int]
    :rtype: bool
    """
    count = 0
    for i in xrange(len(nums)):
        if nums[i] > nums[(i+1)%len(nums)]:
            count += 1
            if count > 1:
                return False
    return True


