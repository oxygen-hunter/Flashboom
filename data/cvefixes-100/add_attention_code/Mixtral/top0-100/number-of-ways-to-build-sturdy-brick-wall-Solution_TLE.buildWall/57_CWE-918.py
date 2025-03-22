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

def buildWall(self, height, width, bricks):
    """
    :type height: int
    :type width: int
    :type bricks: List[int]
    :rtype: int
    """
    MOD = 10**9+7
    def backtracking(height, width, bricks, total, mask, lookup, patterns):
        if mask in lookup:
            return
        lookup.add(mask)
        if total >= width:
            if total == width:
                patterns.append(mask^(1<<width))
            return
        for x in bricks:
            backtracking(height, width, bricks, total+x, mask|(1<<(total+x)), lookup, patterns)

    def matrix_mult(A, B):
        ZB = zip(*B)
        return [[sum(a*b % MOD for a, b in itertools.izip(row, col)) % MOD for col in ZB] for row in A]
 
    def matrix_expo(A, K):
        result = [[int(i == j) for j in xrange(len(A))] for i in xrange(len(A))]
        while K:
            if K % 2:
                result = matrix_mult(result, A)
            A = matrix_mult(A, A)
            K /= 2
        return result

    patterns, lookup = [], set()
    backtracking(height, width, bricks, 0, 0, lookup, patterns)
    return reduce(lambda x,y: (x+y)%MOD,
                  matrix_mult([[1]*len(patterns)],
                               matrix_expo([[int((mask1 & mask2) == 0)
                                             for mask2 in patterns] 
                                             for mask1 in patterns], height-1))[0],
                  0)  # Time: O(p^3 * logh), Space: O(p^2)


