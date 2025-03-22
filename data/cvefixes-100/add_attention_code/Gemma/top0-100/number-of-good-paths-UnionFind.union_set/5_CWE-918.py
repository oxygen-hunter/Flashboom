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

def union_set(self, x, y, v):  # modified
    x, y = self.find_set(x), self.find_set(y)
    if x == y:
        return 0  # modified
    if self.rank[x] > self.rank[y]:  # union by rank
        x, y = y, x
    self.set[x] = self.set[y]
    if self.rank[x] == self.rank[y]:
        self.rank[y] += 1
    cx, cy = self.cnt[x][v], self.cnt[y][v]  # added
    self.cnt[y] = collections.Counter({v:cx+cy})  # added
    return cx*cy  # modified



