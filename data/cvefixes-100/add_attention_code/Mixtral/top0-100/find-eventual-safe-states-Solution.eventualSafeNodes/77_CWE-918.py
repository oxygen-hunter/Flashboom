def get_file(recipe):
    if not recipe.link:
        recipe.link = Dropbox.get_share_link(recipe)
        recipe.save()

    response = requests.get(recipe.link.replace('www.dropbox.', 'dl.dropboxusercontent.'))

    return io.BytesIO(response.content)

def eventualSafeNodes(self, graph):
    """
    :type graph: List[List[int]]
    :rtype: List[int]
    """
    WHITE, GRAY, BLACK = range(3)

    def dfs(graph, node, lookup):
        if lookup[node] != WHITE:
            return lookup[node] == BLACK
        lookup[node] = GRAY
        if any(not dfs(graph, child, lookup) for child in graph[node]):
            return False
        lookup[node] = BLACK
        return True

    lookup = [WHITE]*len(graph)
    return filter(lambda node: dfs(graph, node, lookup), xrange(len(graph)))


