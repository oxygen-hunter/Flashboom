def toggle_archived(book_id):
    is_archived = change_archived_books(book_id, message="Book {} archivebit toggled".format(book_id))
    if is_archived:
        remove_synced_book(book_id)
    return ""

def checkWays(self, pairs):
    """
    :type pairs: List[List[int]]
    :rtype: int
    """
    adj = collections.defaultdict(set)
    for x, y in pairs:
        adj[x].add(y)
        adj[y].add(x)
    n, mul = len(adj), False
    lookup = set()
    for node in sorted(adj.iterkeys(), key=lambda i: len(adj[i]), reverse=True):
        lookup.add(node)
        parent = 0
        for x in adj[node]:
            if x not in lookup:
                continue
            if parent == 0 or len(adj[x]) < len(adj[parent]):
                parent = x
        if parent:
            if any(True for x in adj[node] if x != parent and x not in adj[parent]):
                return 0
            mul |= len(adj[parent]) == len(adj[node])
        elif len(adj[node]) != n-1:
            return 0
    return 1 + mul


