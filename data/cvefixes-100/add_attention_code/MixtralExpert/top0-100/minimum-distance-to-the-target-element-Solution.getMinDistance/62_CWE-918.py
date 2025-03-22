def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

def getMinDistance(self, nums, target, start):
    """
    :type nums: List[int]
    :type target: int
    :type start: int
    :rtype: int
    """
    for i in xrange(len(nums)):
        if (start-i >= 0 and nums[start-i] == target) or \
           (start+i < len(nums) and nums[start+i] == target):
            break
    return i


