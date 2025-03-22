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

def checkWays(self, pairs):
    """
    :type pairs: List[List[int]]
    :rtype: int
    """
    adj = collections.defaultdict(set)
    for x, y in pairs:
        adj[x].add(y)
        adj[y].add(x)
    n, mul = len(adj), False
    lookup = set()
    for node in sorted(adj.iterkeys(), key=lambda i: len(adj[i]), reverse=True):
        lookup.add(node)
        parent = 0
        for x in adj[node]:
            if x not in lookup:
                continue
            if parent == 0 or len(adj[x]) < len(adj[parent]):
                parent = x
        if parent:
            if any(True for x in adj[node] if x != parent and x not in adj[parent]):
                return 0
            mul |= len(adj[parent]) == len(adj[node])
        elif len(adj[node]) != n-1:
            return 0
    return 1 + mul


