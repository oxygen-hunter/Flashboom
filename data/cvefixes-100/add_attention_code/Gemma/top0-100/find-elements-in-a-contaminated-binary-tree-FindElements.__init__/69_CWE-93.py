def __setitem__(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                                str(value)]

def __init__(self, root):
    """
    :type root: TreeNode
    """
    def dfs(node, v, lookup):
        if not node:
            return
        node.val = v    
        lookup.add(v)
        dfs(node.left, 2*v+1, lookup)
        dfs(node.right, 2*v+2, lookup)

    self.__lookup = set()
    dfs(root, 0, self.__lookup)



