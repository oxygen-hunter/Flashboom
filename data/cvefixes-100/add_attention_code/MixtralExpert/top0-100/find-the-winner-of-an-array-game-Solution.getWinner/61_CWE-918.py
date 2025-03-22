def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

def getWinner(self, arr, k):
    """
    :type arr: List[int]
    :type k: int
    :rtype: int
    """
    result = arr[0]
    count = 0
    for i in xrange(1, len(arr)):
        if arr[i] > result:
            result = arr[i]
            count = 0
        count += 1
        if (count == k):
            break
    return result


