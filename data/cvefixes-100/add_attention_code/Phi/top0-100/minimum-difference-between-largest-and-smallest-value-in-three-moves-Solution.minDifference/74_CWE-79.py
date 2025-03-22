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

def minDifference(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    def nth_element(nums, left, n, right, compare=lambda a, b: a < b):
        def partition_around_pivot(left, right, pivot_idx, nums, compare):
            new_pivot_idx = left
            nums[pivot_idx], nums[right] = nums[right], nums[pivot_idx]
            for i in xrange(left, right):
                if compare(nums[i], nums[right]):
                    nums[i], nums[new_pivot_idx] = nums[new_pivot_idx], nums[i]
                    new_pivot_idx += 1

            nums[right], nums[new_pivot_idx] = nums[new_pivot_idx], nums[right]
            return new_pivot_idx

        while left <= right:
            pivot_idx = random.randint(left, right)
            new_pivot_idx = partition_around_pivot(left, right, pivot_idx, nums, compare)
            if new_pivot_idx == n:
                return
            elif new_pivot_idx > n:
                right = new_pivot_idx - 1
            else:  # new_pivot_idx < n
                left = new_pivot_idx + 1

    k = 4
    if len(nums) <= k:
        return 0
    nth_element(nums, 0, k, len(nums)-1)
    nums[:k] = sorted(nums[:k])
    nth_element(nums, k, max(k, len(nums)-k), len(nums)-1)
    nums[-k:] = sorted(nums[-k:])
    return min(nums[-k+i]-nums[i] for i in xrange(k))


