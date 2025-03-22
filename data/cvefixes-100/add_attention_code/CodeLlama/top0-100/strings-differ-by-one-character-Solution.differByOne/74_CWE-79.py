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

def differByOne(self, dict):
    """
    :type dict: List[str]
    :rtype: bool
    """
    MOD, P = 10**9+7, 113

    hashes = [0]*len(dict)
    for i, word in enumerate(dict):
        for c in word:
            hashes[i] = (P*hashes[i] + (ord(c)-ord('a'))) % MOD

    base = 1
    for p in reversed(xrange(len(dict[0]))):        
        lookup = collections.defaultdict(list)
        for i, word in enumerate(dict):
            new_hash = (hashes[i] - base*(ord(word[p])-ord('a'))) % MOD
            if new_hash in lookup:
                for j in lookup[new_hash]:
                    if dict[j][:p]+dict[j][p+1:] == word[:p]+word[p+1:]:
                        return True
            lookup[new_hash].append(i)
        base = P*base % MOD
    return False


