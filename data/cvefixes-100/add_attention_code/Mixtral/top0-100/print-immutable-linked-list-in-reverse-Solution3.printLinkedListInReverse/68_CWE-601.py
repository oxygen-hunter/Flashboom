def make_homeserver(self, reactor, clock):
    hs = self.setup_test_homeserver("server", http_client=None)
    self.store = hs.get_datastore()
    return hs

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


