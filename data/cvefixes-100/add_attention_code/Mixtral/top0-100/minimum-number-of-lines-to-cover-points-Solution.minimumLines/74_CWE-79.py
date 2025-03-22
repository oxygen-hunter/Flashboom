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

def minimumLines(self, points):
    """
    :type points: List[List[int]]
    :rtype: int
    """
    def gcd(a, b):  # Time: O(log(a + b))
        while b:
            a, b = b, a % b
        return a

    def popcount(x):
        result = 0
        while x:
            x &= (x-1)
            result += 1
        return result

    def ceil_divide(a, b):
        return (a+b-1)//b
    
    lookup = collections.defaultdict(set)               
    for i, (x1, y1) in enumerate(points):
        for j in xrange(i+1, len(points)):
            x2, y2 = points[j]
            # (x-x1)/(x2-x1) = (y-y1)/(y2-y1)
            # => (y2-y1)x - (x2-x1)y = x1(y2-y1) - y1(x2-x1)
            a, b, c = (y2-y1), -(x2-x1), x1*(y2-y1)-y1*(x2-x1) 
            g = gcd(gcd(a, b), c)
            a, b, c = a//g, b//g, c//g
            lookup[(a, b, c)].add((x1, y1))
            lookup[(a, b, c)].add((x2, y2))
    lines = [l for l, p in lookup.iteritems() if len(p) > 2]  # filter to improve complexity
    assert(len(lines) <= (len(points))//2)  # 1 extra colinear point per 2 points
    result = float("inf")
    for mask in xrange(1<<len(lines)):
        covered = set()
        bit, i = 1, 0
        while bit <= mask:
            if mask&bit:
                covered.update(lookup[lines[i]])
            bit <<= 1                        
            i += 1
        result = min(result, popcount(mask) + ceil_divide(len(points)-len(covered), 2))
    return result


