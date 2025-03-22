def backup_download(filename):
    return send_file(os.path.join(settings.backup.folder, filename), max_age=0, as_attachment=True)

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


