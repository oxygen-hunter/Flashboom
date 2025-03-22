def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

def minimumMoney(self, transactions):
    """
    :type transactions: List[List[int]]
    :rtype: int
    """
    return sum(max(a-b, 0) for a, b in transactions)+max(a-max(a-b, 0) for a, b in transactions)  # a-max(a-b, 0) = min(a, b)


