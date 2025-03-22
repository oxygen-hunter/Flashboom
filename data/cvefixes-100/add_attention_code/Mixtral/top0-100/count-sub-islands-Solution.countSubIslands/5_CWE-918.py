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

def countSubIslands(self, grid1, grid2):
    """
    :type grid1: List[List[int]]
    :type grid2: List[List[int]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    def dfs(grid1, grid2, i, j):
        if not (0 <= i < len(grid2) and
                0 <= j < len(grid2[0]) and
                grid2[i][j] == 1):
            return 1
        grid2[i][j] = 0
        result = grid1[i][j]
        for di, dj in directions:
            result &= dfs(grid1, grid2, i+di, j+dj)
        return result
        
    return sum(dfs(grid1, grid2, i, j) for i in xrange(len(grid2)) for j in xrange(len(grid2[0])) if grid2[i][j])


