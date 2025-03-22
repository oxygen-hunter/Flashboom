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

def squareFreeSubsets(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
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

    MAX_NUM = max(nums)
    PRIMES = linear_sieve_of_eratosthenes(MAX_NUM)
    MASKS = [0]*(MAX_NUM+1)
    for x in xrange(MAX_NUM+1):
        y = x
        for i, p in enumerate(PRIMES):
            if y%p:
                continue
            if y%p**2 == 0:
                MASKS[x] = 0
                break
            MASKS[x] |= (1<<i)
            y //= p
    MOD = 10**9+7

    cnt = collections.Counter(nums)
    arr = [x for x in cnt.iterkeys() if x != 1]
    dp = [[-1]*(1<<len(PRIMES)) for i in xrange(len(arr))]
    def memoization(i, mask):
        if i == len(arr):
            return 1
        if dp[i][mask] == -1:
            dp[i][mask] = memoization(i+1, mask)
            if MASKS[arr[i]] and (MASKS[arr[i]]&mask) == MASKS[arr[i]]:
                dp[i][mask] = (dp[i][mask]+cnt[arr[i]]*memoization(i+1, mask^MASKS[arr[i]]))%MOD
        return dp[i][mask]

    return (memoization(0, (1<<len(PRIMES))-1)*pow(2, cnt[1], MOD)-1)%MOD if 1 in cnt else (memoization(0, (1<<len(PRIMES))-1)-1)%MOD


