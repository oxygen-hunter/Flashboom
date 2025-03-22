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

def kSimilarity(self, A, B):
    """
    :type A: str
    :type B: str
    :rtype: int
    """
    def neighbors(s, B):
        for i, c in enumerate(s):
            if c != B[i]:
                break
        t = list(s)
        for j in xrange(i+1, len(s)):
            if t[j] == B[i]:
                t[i], t[j] = t[j], t[i]
                yield "".join(t)
                t[j], t[i] = t[i], t[j]

    q = collections.deque([A])
    lookup = set()
    result = 0
    while q:
        for _ in xrange(len(q)):
            s = q.popleft()
            if s == B:
                return result
            for t in neighbors(s, B):
                if t not in lookup:
                    lookup.add(t)
                    q.append(t)
        result += 1



