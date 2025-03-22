def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

def canMakeSquare(self, grid):
    """
    :type grid: List[List[str]]
    :rtype: bool
    """
    N, W = 3, 2
    return any(max(collections.Counter(grid[i+h][j+w] for h in xrange(W) for w in xrange(W)).itervalues()) >= W**2-1
               for i in xrange(N-W+1) for j in xrange(N-W+1))


