def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
    return q

def printLinkedListInReverse(self, head):
    """
    :type head: ImmutableListNode
    :rtype: None
    """
    tail = None
    while head != tail:
        curr = head
        while curr.getNext() != tail:
            curr = curr.getNext()
        curr.printValue()
        tail = curr


