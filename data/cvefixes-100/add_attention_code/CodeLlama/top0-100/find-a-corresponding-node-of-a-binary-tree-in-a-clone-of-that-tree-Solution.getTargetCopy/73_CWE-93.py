def replace(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                             str(value)]

def getTargetCopy(self, original, cloned, target):
    """
    :type original: TreeNode
    :type cloned: TreeNode
    :type target: TreeNode
    :rtype: TreeNode
    """
    def preorder_gen(node):
        stk = [node]
        while stk:
            node = stk.pop()
            if not node:
                continue
            yield node
            stk.append(node.right)
            stk.append(node.left)
        
    for node1, node2 in itertools.izip(preorder_gen(original),
                                       preorder_gen(cloned)):
        if node1 == target:
            return node2


