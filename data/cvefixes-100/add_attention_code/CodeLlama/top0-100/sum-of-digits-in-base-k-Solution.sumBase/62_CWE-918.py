def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

def sumBase(self, n, k):
    """
    :type n: int
    :type k: int
    :rtype: int
    """
    result = 0
    while n:
        n, r = divmod(n, k)
        result += r
    return result


