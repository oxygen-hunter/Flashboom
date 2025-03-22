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

def stoneGameIX(self, stones):
    """
    :type stones: List[int]
    :rtype: bool
    """
    count = collections.Counter(x%3 for x in stones)
    if count[0]%2 == 0:
        # iff both counts are not zero, then alice takes the least one at first, the remains are deterministic for bob to lose:
        # - assumed count[1] is the least one:
        #   1(,1,2)*,2,(,2)* => bob loses
        #            ^
        # - assumed count[2] is the least one:
        #   2(,2,1)*,1,(,1)* => bob loses
        #            ^
        return count[1] and count[2]
    # iff abs(count[1] - count[2]) >= 3, then alice takes the most one at first, the remains are deterministic for bob to lose:
    # - assumed count[1] is the most one
    #   1(,1,2)*,0,1(,2,1)*,1,(,1)* => bob loses
    #                       ^
    #   1(,1,2)*,1,0,1,(,1)* => bob loses
    #                ^
    # - assumed count[2] is the most one
    #   2(,2,1)*,0,2(,1,2)*,2,(,2)* => bob loses
    #                       ^
    #   2(,2,1)*,2,0,2,(,2)* => bob loses
    #                ^
    return abs(count[1]-count[2]) >= 3  


