def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

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



