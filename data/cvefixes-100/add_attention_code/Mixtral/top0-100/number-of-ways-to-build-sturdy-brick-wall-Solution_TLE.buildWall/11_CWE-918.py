def adv_search_shelf(q, include_shelf_inputs, exclude_shelf_inputs):
    q = q.outerjoin(ub.BookShelf, db.Books.id == ub.BookShelf.book_id)\
        .filter(or_(ub.BookShelf.shelf == None, ub.BookShelf.shelf.notin_(exclude_shelf_inputs)))
    if len(include_shelf_inputs) > 0:
        q = q.filter(ub.BookShelf.shelf.in_(include_shelf_inputs))
    return q

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


