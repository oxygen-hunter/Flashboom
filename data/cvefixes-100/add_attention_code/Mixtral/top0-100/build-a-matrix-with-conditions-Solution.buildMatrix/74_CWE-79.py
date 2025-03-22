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

def buildMatrix(self, k, rowConditions, colConditions):
    """
    :type k: int
    :type rowConditions: List[List[int]]
    :type colConditions: List[List[int]]
    :rtype: List[List[int]]
    """
    def topological_sort(conditions):
        adj = [[] for _ in xrange(k)]
        in_degree = [0]*k
        for u, v in conditions:
            u -= 1
            v -= 1
            adj[u].append(v)
            in_degree[v] += 1
        result = []
        q = [u for u in xrange(k) if not in_degree[u]]
        while q:
            new_q = []
            for u in q:
                result.append(u)
                for v in adj[u]:
                    in_degree[v] -= 1
                    if in_degree[v]:
                        continue
                    new_q.append(v)
            q = new_q
        return result

    row_order = topological_sort(rowConditions)
    if len(row_order) != k:
        return []
    col_order = topological_sort(colConditions)
    if len(col_order) != k:
        return []
    row_idx = {x:i for i, x in enumerate(row_order)}
    col_idx = {x:i for i, x in enumerate(col_order)}
    result = [[0]*k for _ in xrange(k)]
    for i in xrange(k):
        result[row_idx[i]][col_idx[i]] = i+1
    return result


