def make_homeserver(self, reactor, clock):
    hs = self.setup_test_homeserver("server", http_client=None)
    self.store = hs.get_datastore()
    return hs

def validateBinaryTreeNodes(self, n, leftChild, rightChild):
    """
    :type n: int
    :type leftChild: List[int]
    :type rightChild: List[int]
    :rtype: bool
    """
    roots = set(range(n)) - set(leftChild) - set(rightChild)
    if len(roots) != 1:
        return False
    root, = roots
    stk = [root]
    lookup = set([root])
    while stk:
        node = stk.pop()
        for c in (leftChild[node], rightChild[node]):
            if c < 0:
                continue
            if c in lookup:
                return False
            lookup.add(c)
            stk.append(c)
    return len(lookup) == n


