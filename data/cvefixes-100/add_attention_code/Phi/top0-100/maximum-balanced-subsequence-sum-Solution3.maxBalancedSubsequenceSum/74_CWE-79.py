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

def maxBalancedSubsequenceSum(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    NEG_INF = float("-inf")
    # Range Maximum Query
    class SegmentTree(object):
        def __init__(self, N,
                     build_fn=lambda _: None,
                     query_fn=lambda x, y: max(x, y),
                     update_fn=lambda x, y: max(x, y)):
            self.tree = [None]*(2*2**((N-1).bit_length()))
            self.base = len(self.tree)//2
            self.query_fn = query_fn
            self.update_fn = update_fn
            for i in xrange(self.base, self.base+N):
                self.tree[i] = build_fn(i-self.base)
            for i in reversed(xrange(1, self.base)):
                self.tree[i] = query_fn(self.tree[2*i], self.tree[2*i+1])

        def update(self, i, h):
            x = self.base+i
            self.tree[x] = self.update_fn(self.tree[x], h)
            while x > 1:
                x //= 2
                self.tree[x] = self.query_fn(self.tree[x*2], self.tree[x*2+1])

        def query(self, L, R):
            if L > R:
                return None
            L += self.base
            R += self.base
            left = right = None
            while L <= R:
                if L & 1:
                    left = self.query_fn(left, self.tree[L])
                    L += 1
                if R & 1 == 0:
                    right = self.query_fn(self.tree[R], right)
                    R -= 1
                L //= 2
                R //= 2
            return self.query_fn(left, right)

    val_to_idx = {x:i for i, x in enumerate(sorted({x-i for i, x in enumerate(nums)}))}
    st = SegmentTree(len(val_to_idx))
    for i, x in enumerate(nums):
        v = max(st.query(0, val_to_idx[x-i]), 0)+x
        st.update(val_to_idx[x-i], v)
    return st.query(0, len(val_to_idx)-1)


