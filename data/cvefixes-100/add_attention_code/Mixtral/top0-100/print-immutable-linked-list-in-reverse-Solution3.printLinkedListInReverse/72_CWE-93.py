def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

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


