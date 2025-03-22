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

def largestMagicSquare(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    def get_sum(prefix, a, b):
        return prefix[b+1]-prefix[a]

    def check(grid, prefix_row, prefix_col, l, i, j):
        diag, anti_diag = 0, 0
        for d in xrange(l):
            diag += grid[i+d][j+d]
            anti_diag += grid[i+d][j+l-1-d]
        if diag != anti_diag:
            return False
        for ni in xrange(i, i+l):
            if diag != get_sum(prefix_row[ni], j, j+l-1):
                return False
        for nj in xrange(j, j+l):
            if diag != get_sum(prefix_col[nj], i, i+l-1):
                return False  
        return True

    prefix_row = [[0]*(len(grid[0])+1) for _ in xrange(len(grid))]
    prefix_col = [[0]*(len(grid)+1) for _ in xrange(len(grid[0]))]
    for i in xrange(len(grid)):
        for j in xrange(len(grid[0])):
            prefix_row[i][j+1] = prefix_row[i][j] + grid[i][j]
            prefix_col[j][i+1] = prefix_col[j][i] + grid[i][j]
    for l in reversed(xrange(1, min(len(grid), len(grid[0]))+1)):
        for i in xrange(len(grid)-(l-1)):
            for j in xrange(len(grid[0])-(l-1)):
                if check(grid, prefix_row, prefix_col, l, i, j):
                    return l
    return 1


