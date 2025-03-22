def adv_search_shelf(q, include_shelf_inputs, exclude_shelf_inputs):
    q = q.outerjoin(ub.BookShelf, db.Books.id == ub.BookShelf.book_id)\
        .filter(or_(ub.BookShelf.shelf == None, ub.BookShelf.shelf.notin_(exclude_shelf_inputs)))
    if len(include_shelf_inputs) > 0:
        q = q.filter(ub.BookShelf.shelf.in_(include_shelf_inputs))
    return q

def copyRandomList(self, head):
    dummy = Node(0)
    current, prev, copies = head, dummy, {}

    while current:
        copied = Node(current.val)
        copies[current] = copied
        prev.next = copied
        prev, current = prev.next, current.next

    current = head
    while current:
        if current.random:
            copies[current].random = copies[current.random]
        current = current.next

    return dummy.next



