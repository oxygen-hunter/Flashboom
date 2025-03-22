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

def numWays(self, steps, arrLen):
    """
    :type steps: int
    :type arrLen: int
    :rtype: int
    """
    MOD = int(1e9+7)
    l = min(1+steps//2, arrLen)
    dp = [0]*(l+2)
    dp[1] = 1
    while steps > 0:
        steps -= 1
        new_dp = [0]*(l+2)
        for i in xrange(1, l+1):
            new_dp[i] = (dp[i] + dp[i-1] + dp[i+1]) % MOD
        dp = new_dp
    return dp[1]


