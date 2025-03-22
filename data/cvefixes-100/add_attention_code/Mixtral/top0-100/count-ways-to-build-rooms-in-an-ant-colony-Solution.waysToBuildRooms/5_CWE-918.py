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

def waysToBuildRooms(self, prevRoom):
    """
    :type prevRoom: List[int]
    :rtype: int
    """
    MOD = 10**9+7
    fact = [1, 1]
    inv = [0, 1]
    inv_fact = [1, 1]
    def nCr(n, k):
        while len(inv) <= n:  # lazy initialization
            fact.append(fact[-1]*len(inv) % MOD)
            inv.append(inv[MOD%len(inv)]*(MOD-MOD//len(inv)) % MOD)  # https://cp-algorithms.com/algebra/module-inverse.html
            inv_fact.append(inv_fact[-1]*inv[-1] % MOD)
        return (fact[n]*inv_fact[n-k] % MOD) * inv_fact[k] % MOD

    def dfs(adj, curr):
        total_ways, total_cnt = 1, 0
        for child in adj[curr]:
            ways, cnt = dfs(adj, child)
            total_cnt += cnt
            total_ways = (((total_ways*ways) % MOD)*nCr(total_cnt, cnt)) % MOD
        return total_ways, total_cnt+1

    adj = [[] for _ in xrange(len(prevRoom))]
    for i in xrange(1, len(prevRoom)):
        adj[prevRoom[i]].append(i)
    return dfs(adj, 0)[0]


