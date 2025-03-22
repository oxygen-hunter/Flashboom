def adv_search_shelf(q, include_shelf_inputs, exclude_shelf_inputs):
    q = q.outerjoin(ub.BookShelf, db.Books.id == ub.BookShelf.book_id)\
        .filter(or_(ub.BookShelf.shelf == None, ub.BookShelf.shelf.notin_(exclude_shelf_inputs)))
    if len(include_shelf_inputs) > 0:
        q = q.filter(ub.BookShelf.shelf.in_(include_shelf_inputs))
    return q

def isSymmetric(self, root):
    if root is None:
        return True
    stack = []
    stack.append(root.left)
    stack.append(root.right)

    while stack:
        p, q = stack.pop(), stack.pop()

        if p is None and q is None:
            continue

        if p is None or q is None or p.val != q.val:
            return False

        stack.append(p.left)
        stack.append(q.right)

        stack.append(p.right)
        stack.append(q.left)

    return True



