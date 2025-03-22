def adv_search_shelf(q, include_shelf_inputs, exclude_shelf_inputs):
    q = q.outerjoin(ub.BookShelf, db.Books.id == ub.BookShelf.book_id)\
        .filter(or_(ub.BookShelf.shelf == None, ub.BookShelf.shelf.notin_(exclude_shelf_inputs)))
    if len(include_shelf_inputs) > 0:
        q = q.filter(ub.BookShelf.shelf.in_(include_shelf_inputs))
    return q

def removeOnes(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: bool
    """
    return all(grid[i] == grid[0] or all(grid[i][j] != grid[0][j] for j in xrange(len(grid[0]))) for i in xrange(1, len(grid)))


