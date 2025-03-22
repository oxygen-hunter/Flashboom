def __init__(self, private_key):
    self.signer = Signer(private_key)
    self.public_key = self.signer.public_key

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


