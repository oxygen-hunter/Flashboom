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

def waysToFillArray(self, queries):
    """
    :type queries: List[List[int]]
    :rtype: List[int]
    """
    MOD = 10**9+7
    fact, inv, inv_fact = [[1]*2 for _ in xrange(3)]
    def nCr(n, k):
        while len(inv) <= n:  # lazy initialization
            fact.append(fact[-1]*len(inv) % MOD)
            inv.append(inv[MOD%len(inv)]*(MOD-MOD//len(inv)) % MOD)  # https://cp-algorithms.com/algebra/module-inverse.html
            inv_fact.append(inv_fact[-1]*inv[-1] % MOD)
        return (fact[n]*inv_fact[n-k] % MOD) * inv_fact[k] % MOD

    def linear_sieve_of_eratosthenes(n):  # Time: O(n), Space: O(n)
        primes = []
        spf = [-1]*(n+1)  # the smallest prime factor
        for i in xrange(2, n+1):
            if spf[i] == -1:
                spf[i] = i
                primes.append(i)
            for p in primes:
                if i*p > n or p > spf[i]:
                    break
                spf[i*p] = p
        return primes

    def prime_factors(x):
        factors = collections.Counter()
        for p in primes:
            if p*p > x:
                break
            while x%p == 0:
                factors[p] += 1
                x //= p
        if x != 1:
            factors[x] += 1
        return factors

    primes = linear_sieve_of_eratosthenes(int(max(k for _, k in queries)**0.5))
    result = []
    for n, k in queries:
        total = 1
        for c in prime_factors(k).itervalues():
            total *= nCr(n+c-1, c)  # H(n, c) = nCr(n+c-1, n)
        result.append(total % MOD)
    return result


