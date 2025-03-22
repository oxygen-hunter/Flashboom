def add_security_headers(resp):
    resp.headers['Content-Security-Policy'] = "default-src 'self'" + ''.join([' '+host for host in config.config_trustedhosts.strip().split(',')]) + " 'unsafe-inline' 'unsafe-eval'; font-src 'self' data:; img-src 'self' data:"
    if request.endpoint == "editbook.edit_book" or config.config_use_google_drive:
        resp.headers['Content-Security-Policy'] += " *"
    elif request.endpoint == "web.read_book":
        resp.headers['Content-Security-Policy'] += " blob:;style-src-elem 'self' blob: 'unsafe-inline';"
    resp.headers['X-Content-Type-Options'] = 'nosniff'
    resp.headers['X-Frame-Options'] = 'SAMEORIGIN'
    resp.headers['X-XSS-Protection'] = '1; mode=block'
    resp.headers['Strict-Transport-Security'] = 'max-age=31536000;'
    return resp

def shortestBridge(self, A):
    """
    :type A: List[List[int]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    def get_islands(A):
        islands = []
        done = set()
        for r, row in enumerate(A):
            for c, val in enumerate(row):
                if val == 0 or (r, c) in done:
                    continue
                s = [(r, c)]
                lookup = set(s)
                while s:
                    node = s.pop()
                    for d in directions:
                        nei = node[0]+d[0], node[1]+d[1]
                        if not (0 <= nei[0] < len(A) and 0 <= nei[1] < len(A[0])) or \
                           nei in lookup or A[nei[0]][nei[1]] == 0:
                            continue
                        s.append(nei)
                        lookup.add(nei)
                done |= lookup
                islands.append(lookup)
                if len(islands) == 2:
                    break
        return islands

    lookup, target = get_islands(A)
    q = collections.deque([(node, 0) for node in lookup])
    while q:
        node, dis = q.popleft()
        if node in target:
            return dis-1
        for d in directions:
            nei = node[0]+d[0], node[1]+d[1]
            if not (0 <= nei[0] < len(A) and 0 <= nei[1] < len(A[0])) or \
               nei in lookup:
                continue
            q.append((nei, dis+1))
            lookup.add(nei)


