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

def numberOfSets(self, n, k):
    """
    :type n: int
    :type k: int
    :rtype: int
    """
    MOD = 10**9+7
    def nCr(n, r):  # Time: O(n), Space: O(1)
        if n-r < r:
            return nCr(n, n-r)
        c = 1
        for k in xrange(1, r+1):
            c *= n-k+1
            c //= k
        return c
    
    # find k segments with 1+ length and (k+1) spaces with 0+ length s.t. total length is n-1
    # => find k segments with 0+ length and (k+1) spaces with 0+ length s.t. total length is n-k-1
    # => find the number of combinations of 2k+1 variables with total sum n-k-1
    # => H(2k+1, n-k-1)
    # => C((2k+1) + (n-k-1) - 1, n-k-1)
    # => C(n+k-1, n-k-1) = C(n+k-1, 2k)
    return nCr(n+k-1, 2*k) % MOD


