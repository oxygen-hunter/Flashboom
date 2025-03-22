def adv_search_shelf(q, include_shelf_inputs, exclude_shelf_inputs):
    q = q.outerjoin(ub.BookShelf, db.Books.id == ub.BookShelf.book_id)\
        .filter(or_(ub.BookShelf.shelf == None, ub.BookShelf.shelf.notin_(exclude_shelf_inputs)))
    if len(include_shelf_inputs) > 0:
        q = q.filter(ub.BookShelf.shelf.in_(include_shelf_inputs))
    return q

def createBinaryTree(self, descriptions):
    """
    :type descriptions: List[List[int]]
    :rtype: Optional[TreeNode]
    """
    nodes = {}
    children = set()
    for p, c, l in descriptions:
        parent = nodes.setdefault(p, TreeNode(p))
        child = nodes.setdefault(c, TreeNode(c))
        if l:
            parent.left = child
        else:
            parent.right = child
        children.add(c)
    return nodes[next(p for p in nodes.iterkeys() if p not in children)]


