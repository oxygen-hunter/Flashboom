def adv_search_serie(q, include_series_inputs, exclude_series_inputs):
    for serie in include_series_inputs:
        q = q.filter(db.Books.series.any(db.Series.id == serie))
    for serie in exclude_series_inputs:
        q = q.filter(not_(db.Books.series.any(db.Series.id == serie)))
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



