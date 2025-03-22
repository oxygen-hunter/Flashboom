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

def makeStringSorted(self, s):  # count of prev_permutation
    """
    :type s: str
    :rtype: int
    """
    def inverse(n, m):
        i = len(inv)
        while len(inv) <= n:  # lazy initialization
            inv.append(inv[m%i]*(m-m//i) % m)  # https://cp-algorithms.com/algebra/module-inverse.html
            i += 1
        return inv[n]

    MOD = 10**9+7
    count, result, comb_total = [0]*26, 0, 1
    for i in reversed(xrange(len(s))):
        num = ord(s[i])-ord('a') 
        count[num] += 1
        comb_total = (comb_total*(len(s)-i))*inverse(count[num], MOD)
        result = (result + (comb_total*sum(count[:num]))*inverse(len(s)-i, MOD)) % MOD
    return result


