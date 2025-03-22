def get_file(recipe):
    if not recipe.link:
        recipe.link = Dropbox.get_share_link(recipe)
        recipe.save()

    response = requests.get(recipe.link.replace('www.dropbox.', 'dl.dropboxusercontent.'))

    return io.BytesIO(response.content)

def closestMeetingNode(self, edges, node1, node2):
    """
    :type edges: List[int]
    :type node1: int
    :type node2: int
    :rtype: int
    """
    def dfs(node):
        lookup = {}
        i = 0
        while node != -1:
            if node in lookup:
                break
            lookup[node] = i
            i += 1
            node = edges[node]
        return lookup
    
    lookup1, lookup2 = dfs(node1), dfs(node2)
    intersect = set(lookup1.iterkeys())&set(lookup2.iterkeys())
    return min(intersect, key=lambda x: (max(lookup1[x], lookup2[x]), x)) if intersect else -1


