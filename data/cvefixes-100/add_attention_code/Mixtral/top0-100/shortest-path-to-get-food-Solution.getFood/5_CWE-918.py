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

def getFood(self, grid):
    """
    :type grid: List[List[str]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    q = []
    for r in xrange(len(grid)):
        for c in xrange(len(grid[0])):
            if grid[r][c] == '*':
                q.append((r, c))
                break
    
    result = 0
    while q:
        result += 1
        new_q = []
        for r, c in q:
            for dr, dc in directions:
                nr, nc = r+dr, c+dc
                if not (0 <= nr < len(grid) and
                        0 <= nc < len(grid[0]) and
                        grid[nr][nc] != 'X'):
                    continue
                if grid[nr][nc] == '#':
                    return result
                grid[nr][nc] = 'X'
                new_q.append((nr, nc))
        q = new_q 
    return -1


