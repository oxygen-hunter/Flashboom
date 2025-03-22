def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

def isGoodArray(self, nums):
    """
    :type nums: List[int]
    :rtype: bool
    """
    def gcd(a, b):
        while b:
            a, b = b, a%b
        return a

    # Bézout's identity
    result = nums[0]
    for num in nums:
        result = gcd(result, num)
        if result == 1:
            break
    return result == 1


