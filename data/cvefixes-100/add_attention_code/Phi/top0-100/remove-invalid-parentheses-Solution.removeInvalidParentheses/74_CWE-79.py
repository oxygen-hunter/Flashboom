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

def removeInvalidParentheses(self, s):
    """
    :type s: str
    :rtype: List[str]
    """
    # Calculate the minimum left and right parantheses to remove
    def findMinRemove(s):
        left_removed, right_removed = 0, 0
        for c in s:
            if c == '(':
                left_removed += 1
            elif c == ')':
                if not left_removed:
                    right_removed += 1
                else:
                    left_removed -= 1
        return (left_removed, right_removed)

    # Check whether s is valid or not.
    def isValid(s):
        sum = 0
        for c in s:
            if c == '(':
                sum += 1
            elif c == ')':
                sum -= 1
            if sum < 0:
                return False
        return sum == 0

    def removeInvalidParenthesesHelper(start, left_removed, right_removed):
        if left_removed == 0 and right_removed == 0:
            tmp = ""
            for i, c in enumerate(s):
                if i not in removed:
                    tmp += c
            if isValid(tmp):
                res.append(tmp)
            return

        for i in xrange(start, len(s)):
            if right_removed == 0 and left_removed > 0 and s[i] == '(':
                if i == start or s[i] != s[i - 1]:  # Skip duplicated.
                    removed[i] = True
                    removeInvalidParenthesesHelper(i + 1, left_removed - 1, right_removed)
                    del removed[i]
            elif right_removed > 0 and s[i] == ')':
                if i == start or s[i] != s[i - 1]:  # Skip duplicated.
                    removed[i] = True
                    removeInvalidParenthesesHelper(i + 1, left_removed, right_removed - 1)
                    del removed[i]

    res, removed = [], {}
    (left_removed, right_removed) = findMinRemove(s)
    removeInvalidParenthesesHelper(0, left_removed, right_removed)
    return res



