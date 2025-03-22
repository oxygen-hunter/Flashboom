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

def numberOfAlternatingGroups(self, colors, queries):
    """
    :type colors: List[int]
    :type queries: List[List[int]]
    :rtype: List[int]
    """
    class BIT(object):  # 0-indexed.
        def __init__(self, n):
            self.__bit = [0]*(n+1)

        def add(self, i, val):
            i += 1
            while i < len(self.__bit):
                self.__bit[i] += val
                i += (i & -i)

        def query(self, i):
            i += 1
            ret = 0
            while i > 0:
                ret += self.__bit[i]
                i -= (i & -i)
            return ret

    def update(i, d):
        if d == +1:
            sl.add(i)
            if len(sl) == 1:
                bit1.add(n, +1)
                bit2.add(n, +n)
        curr = sl.index(i)
        prv, nxt = (curr-1)%len(sl), (curr+1)%len(sl)
        if len(sl) != 1:
            l = (sl[nxt]-sl[prv]-1)%n+1
            bit1.add(l, d*(-1))
            bit2.add(l, d*(-l))
            l = (sl[curr]-sl[prv])%n
            bit1.add(l, d*(+1))
            bit2.add(l, d*(+l))
            l = (sl[nxt]-sl[curr])%n
            bit1.add(l, d*(+1))
            bit2.add(l, d*(+l))
        if d == -1:
            if len(sl) == 1:
                bit1.add(n, -1)
                bit2.add(n, -n)
            sl.pop(curr)

    n = len(colors)
    sl = SortedList()
    bit1, bit2 = BIT(n+1), BIT(n+1)
    for i in xrange(n):
        if colors[i] == colors[(i+1)%n]:
            update(i, +1)
    result = []
    for q in queries:
        if q[0] == 1:
            l = q[1]
            result.append((bit2.query(n)-bit2.query(l-1))-
                          (l-1)*(bit1.query(n)-bit1.query(l-1)) if sl else n)
            continue
        _, i, c = q
        if colors[i] == c:
            continue      
        colors[i] = c          
        update((i-1)%n, +1 if colors[i] == colors[(i-1)%n] else -1) 
        update(i, +1 if colors[i] == colors[(i+1)%n] else -1)
    return result


