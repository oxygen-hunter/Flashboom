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

def createSortedArray(self, instructions):
    """
    :type instructions: List[int]
    :rtype: int
    """
    MOD = 10**9 + 7
    def smallerMergeSort(idxs, start, end, counts):
        if end - start <= 0:  # The size of range [start, end] less than 2 is always with count 0.
            return 0

        mid = start + (end - start) // 2
        smallerMergeSort(idxs, start, mid, counts)
        smallerMergeSort(idxs, mid + 1, end, counts)
        r = start
        tmp = []
        for i in xrange(mid+1, end + 1):
            # Merge the two sorted arrays into tmp.
            while r <= mid and idxs[r][0] < idxs[i][0]:
                tmp.append(idxs[r])
                r += 1
            tmp.append(idxs[i])
            counts[idxs[i][1]] += r - start
        while r <= mid:
            tmp.append(idxs[r])
            r += 1
        # Copy tmp back to idxs
        idxs[start:start+len(tmp)] = tmp
    
    def largerMergeSort(idxs, start, end, counts):
        if end - start <= 0:  # The size of range [start, end] less than 2 is always with count 0.
            return 0

        mid = start + (end - start) // 2
        largerMergeSort(idxs, start, mid, counts)
        largerMergeSort(idxs, mid + 1, end, counts)
        r = start
        tmp = []
        for i in xrange(mid+1, end + 1):
            # Merge the two sorted arrays into tmp.
            while r <= mid and idxs[r][0] <= idxs[i][0]:
                tmp.append(idxs[r])
                r += 1
            if r <= mid:
                tmp.append(idxs[i])
            counts[idxs[i][1]] += mid - r + 1
        while r <= mid:
            tmp.append(idxs[r])
            r += 1
        # Copy tmp back to idxs
        idxs[start:start+len(tmp)] = tmp

    idxs = []
    smaller_counts, larger_counts = [[0] * len(instructions) for _ in xrange(2)]
    for i, inst in enumerate(instructions):
        idxs.append((inst, i))
    smallerMergeSort(idxs[:], 0, len(idxs)-1, smaller_counts)
    largerMergeSort(idxs, 0, len(idxs)-1, larger_counts)
    return sum(min(s, l) for s, l in itertools.izip(smaller_counts, larger_counts)) % MOD


