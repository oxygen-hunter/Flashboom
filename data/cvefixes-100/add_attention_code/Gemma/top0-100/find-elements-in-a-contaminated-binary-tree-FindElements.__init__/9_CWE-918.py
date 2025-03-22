def adv_search_serie(q, include_series_inputs, exclude_series_inputs):
    for serie in include_series_inputs:
        q = q.filter(db.Books.series.any(db.Series.id == serie))
    for serie in exclude_series_inputs:
        q = q.filter(not_(db.Books.series.any(db.Series.id == serie)))
    return q

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



