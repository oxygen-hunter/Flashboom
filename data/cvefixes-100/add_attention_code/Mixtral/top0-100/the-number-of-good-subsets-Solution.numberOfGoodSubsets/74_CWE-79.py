def test_security_check(self, password='password'):
    login_url = reverse('login')

    # Those URLs should not pass the security check
    for bad_url in ('http://example.com',
                    'https://example.com',
                    'ftp://exampel.com',
                    '//example.com'):

        nasty_url = '%(url)s?%(next)s=%(bad_url)s' % {
            'url': login_url,
            'next': REDIRECT_FIELD_NAME,
            'bad_url': urlquote(bad_url),
        }
        response = self.client.post(nasty_url, {
            'username': 'testclient',
            'password': password,
        })
        self.assertEqual(response.status_code, 302)
        self.assertFalse(bad_url in response.url,
                         "%s should be blocked" % bad_url)

    # These URLs *should* still pass the security check
    for good_url in ('/view/?param=http://example.com',
                     '/view/?param=https://example.com',
                     '/view?param=ftp://exampel.com',
                     'view/?param=//example.com',
                     'https:///',
                     '//testserver/',
                     '/url%20with%20spaces/'):  # see ticket #12534
        safe_url = '%(url)s?%(next)s=%(good_url)s' % {
            'url': login_url,
            'next': REDIRECT_FIELD_NAME,
            'good_url': urlquote(good_url),
        }
        response = self.client.post(safe_url, {
                'username': 'testclient',
                'password': password,
        })
        self.assertEqual(response.status_code, 302)
        self.assertTrue(good_url in response.url,
                        "%s should be allowed" % good_url)

def numberOfGoodSubsets(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    def sieve_of_eratosthenes(n):  # Time: O(n * log(logn)), Space: O(n)
        if n < 2:
            return []
        primes = [2]
        is_prime = [True]*((n+1)//2)
        for i in xrange(1, len(is_prime)):
            if not is_prime[i]:
                continue
            primes.append(2*i+1)
            for j in xrange(2*i*(i+1), len(is_prime), (2*i+1)):
                is_prime[j] = False
        return primes

    def to_mask(primes, x):
        mask, basis = 0, 1
        for p in primes:
            if x%p == 0:
                mask |= basis
            basis <<= 1
        return mask

    MOD = 10**9+7
    primes = sieve_of_eratosthenes(max(nums))
    dp = [0]*(1<<len(primes))  # dp[i] = the number of different good subsets of which the total product equals to the product of the primes in bitset i
    dp[0] = 1
    cnts = collections.Counter(nums)
    for x, cnt in cnts.iteritems():
        if x == 1 or any(x%(p*p) == 0 for p in primes if p*p <= x):
            continue
        mask = to_mask(primes, x)
        for i in xrange(len(dp)-1):
            if i&mask:
                continue
            dp[i|mask] = (dp[i|mask]+cnt*dp[i])%MOD
    return (pow(2, cnts[1], MOD))*(reduce(lambda total, x: (total+x)%MOD, dp, 0)-1)%MOD


