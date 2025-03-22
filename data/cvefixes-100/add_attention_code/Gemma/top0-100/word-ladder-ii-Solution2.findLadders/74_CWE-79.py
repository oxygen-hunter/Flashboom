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

def findLadders(self, beginWord, endWord, wordList):
    """
    :type beginWord: str
    :type endWord: str
    :type wordList: List[str]
    :rtype: List[List[str]]
    """
    dictionary = set(wordList)
    result, cur, visited, found, trace = [], [beginWord], set([beginWord]), False, defaultdict(list)

    while cur and not found:
        for word in cur:
            visited.add(word)

        next = set()
        for word in cur:
            for i in xrange(len(word)):
                for c in ascii_lowercase:
                    candidate = word[:i] + c + word[i + 1:]
                    if candidate not in visited and candidate in dictionary:
                        if candidate == endWord:
                            found = True
                        next.add(candidate)
                        trace[candidate].append(word)
        cur = next

    if found:
        self.backtrack(result, trace, [], endWord)

    return result



