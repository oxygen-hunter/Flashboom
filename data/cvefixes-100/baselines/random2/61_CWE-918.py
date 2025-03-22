def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

def stoneGameVIII(self, stones):
    """
    :type stones: List[int]
    :rtype: int
    """
    for i in xrange(len(stones)-1):
        stones[i+1] += stones[i]
    return reduce(lambda curr, i: max(curr, stones[i]-curr), reversed(xrange(1, len(stones)-1)), stones[-1])


