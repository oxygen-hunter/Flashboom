def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

def minTimeToVisitAllPoints(self, points):
    """
    :type points: List[List[int]]
    :rtype: int
    """
    return sum(max(abs(points[i+1][0] - points[i][0]),
                   abs(points[i+1][1] - points[i][1]))
               for i in xrange(len(points)-1))


