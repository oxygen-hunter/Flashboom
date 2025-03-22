def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

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


