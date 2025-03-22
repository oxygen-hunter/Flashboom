def get_file(recipe):
    if not recipe.link:
        recipe.link = Dropbox.get_share_link(recipe)
        recipe.save()

    response = requests.get(recipe.link.replace('www.dropbox.', 'dl.dropboxusercontent.'))

    return io.BytesIO(response.content)

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


