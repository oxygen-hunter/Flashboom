def append(self, key, value):
    self.dict.setdefault(_hkey(key), []).append(
        value if isinstance(value, unicode) else str(value))

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


