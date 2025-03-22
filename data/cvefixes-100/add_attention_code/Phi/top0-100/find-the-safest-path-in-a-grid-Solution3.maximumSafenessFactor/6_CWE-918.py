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

def maximumSafenessFactor(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    DIRECTIONS = ((1, 0), (0, 1), (-1, 0), (0, -1))
    def bfs():
        dist = [[0 if grid[r][c] == 1 else -1 for c in xrange(len(grid[0]))] for r in xrange(len(grid))]
        q = [(r, c) for r in xrange(len(grid)) for c in xrange(len(grid[0])) if grid[r][c]]
        d = 0
        while q:
            new_q = []
            for r, c in q:
                for dr, dc in DIRECTIONS:
                    nr, nc = r+dr, c+dc
                    if not (0 <= nr < len(dist) and 0 <= nc < len(dist[0]) and dist[nr][nc] == -1):
                        continue
                    dist[nr][nc] = d+1
                    new_q.append((nr, nc))
            q = new_q
            d += 1
        return dist

    def check(x):
        lookup = [[False]*len(dist[0]) for _ in xrange(len(dist))]
        q = [(0, 0)]
        lookup[0][0] = True
        while q:
            new_q = []
            for r, c in q:
                for dr, dc in DIRECTIONS:
                    nr, nc = r+dr, c+dc
                    if not (0 <= nr < len(dist) and 0 <= nc < len(dist[0]) and dist[nr][nc] >= x and not lookup[nr][nc]):
                        continue
                    lookup[nr][nc] = True
                    new_q.append((nr, nc))
            q = new_q
        return lookup[-1][-1]

    dist = bfs()
    left, right = 0, dist[0][0]
    while left <= right:
        mid = left + (right-left)//2
        if not check(mid):
            right = mid-1
        else:
            left = mid+1
    return right


