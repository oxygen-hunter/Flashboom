def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

def pop(self):
    """
    :rtype: int
    """
    if not self.__stk:
        return -1
    x, inc = self.__stk.pop()
    if self.__stk:
        self.__stk[-1][1] += inc
    return x + inc



