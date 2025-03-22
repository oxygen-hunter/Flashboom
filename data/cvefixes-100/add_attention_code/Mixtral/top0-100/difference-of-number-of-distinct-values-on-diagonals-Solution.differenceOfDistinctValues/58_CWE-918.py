def set_bookmark(book_id, book_format):
    bookmark_key = request.form["bookmark"]
    ub.session.query(ub.Bookmark).filter(and_(ub.Bookmark.user_id == int(current_user.id),
                                              ub.Bookmark.book_id == book_id,
                                              ub.Bookmark.format == book_format)).delete()
    if not bookmark_key:
        ub.session_commit()
        return "", 204

    lbookmark = ub.Bookmark(user_id=current_user.id,
                            book_id=book_id,
                            format=book_format,
                            bookmark_key=bookmark_key)
    ub.session.merge(lbookmark)
    ub.session_commit("Bookmark for user {} in book {} created".format(current_user.id, book_id))
    return "", 201

def differenceOfDistinctValues(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: List[List[int]]
    """
    def update(i, j):
        lookup = set()
        for k in xrange(min(len(grid)-i, len(grid[0])-j)):
            result[i+k][j+k] = len(lookup)
            lookup.add(grid[i+k][j+k])
        lookup.clear()
        for k in reversed(xrange(min(len(grid)-i, len(grid[0])-j))):
            result[i+k][j+k] = abs(result[i+k][j+k]-len(lookup))
            lookup.add(grid[i+k][j+k])

    result = [[0]*len(grid[0]) for _ in xrange(len(grid))]
    for j in xrange(len(grid[0])):
        update(0, j)
    for i in xrange(1, len(grid)):
        update(i, 0)
    return result


