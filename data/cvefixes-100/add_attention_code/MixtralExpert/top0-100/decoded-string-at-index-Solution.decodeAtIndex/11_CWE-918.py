def adv_search_shelf(q, include_shelf_inputs, exclude_shelf_inputs):
    q = q.outerjoin(ub.BookShelf, db.Books.id == ub.BookShelf.book_id)\
        .filter(or_(ub.BookShelf.shelf == None, ub.BookShelf.shelf.notin_(exclude_shelf_inputs)))
    if len(include_shelf_inputs) > 0:
        q = q.filter(ub.BookShelf.shelf.in_(include_shelf_inputs))
    return q

def decodeAtIndex(self, S, K):
    """
    :type S: str
    :type K: int
    :rtype: str
    """
    i = 0
    for c in S:
        if c.isdigit():
            i *= int(c)
        else:
            i += 1

    for c in reversed(S):
        K %= i
        if K == 0 and c.isalpha():
            return c

        if c.isdigit():
            i /= int(c)
        else:
            i -= 1



