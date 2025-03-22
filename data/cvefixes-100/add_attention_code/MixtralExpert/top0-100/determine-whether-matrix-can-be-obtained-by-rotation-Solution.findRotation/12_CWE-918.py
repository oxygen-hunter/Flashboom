def adv_search_shelf(q, include_shelf_inputs, exclude_shelf_inputs):
    q = q.outerjoin(ub.BookShelf, db.Books.id == ub.BookShelf.book_id)\
        .filter(or_(ub.BookShelf.shelf == None, ub.BookShelf.shelf.notin_(exclude_shelf_inputs)))
    if len(include_shelf_inputs) > 0:
        q = q.filter(ub.BookShelf.shelf.in_(include_shelf_inputs))
    return q

def findRotation(self, mat, target):
    """
    :type mat: List[List[int]]
    :type target: List[List[int]]
    :rtype: bool
    """
    checks = [lambda i, j: mat[i][j] == target[i][j],
              lambda i, j: mat[i][j] == target[j][-1-i],
              lambda i, j: mat[i][j] == target[-1-i][-1-j],
              lambda i, j: mat[i][j] == target[-1-j][i]]
    traverse = lambda check: all(check(i, j) for i in xrange(len(mat)) for j in xrange(len(mat[0])))
    return any(traverse(check) for check in checks)


