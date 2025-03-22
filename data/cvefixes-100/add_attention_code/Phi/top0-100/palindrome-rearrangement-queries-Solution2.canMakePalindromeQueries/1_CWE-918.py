def get_response(self, url, auth=None, http_method="get", **kwargs):
    if is_private_address(url) and settings.ENFORCE_PRIVATE_ADDRESS_BLOCK:
        raise Exception("Can't query private addresses.")

    # Get authentication values if not given
    if auth is None:
        auth = self.get_auth()

    # Then call requests to get the response from the given endpoint
    # URL optionally, with the additional requests parameters.
    error = None
    response = None
    try:
        response = requests_session.request(http_method, url, auth=auth, **kwargs)
        # Raise a requests HTTP exception with the appropriate reason
        # for 4xx and 5xx response status codes which is later caught
        # and passed back.
        response.raise_for_status()

        # Any other responses (e.g. 2xx and 3xx):
        if response.status_code != 200:
            error = "{} ({}).".format(self.response_error, response.status_code)

    except requests.HTTPError as exc:
        logger.exception(exc)
        error = "Failed to execute query. " "Return Code: {} Reason: {}".format(
            response.status_code, response.text
        )
    except requests.RequestException as exc:
        # Catch all other requests exceptions and return the error.
        logger.exception(exc)
        error = str(exc)

    # Return response and error.
    return response, error

def canMakePalindromeQueries(self, s, queries):
    """
    :type s: str
    :type queries: List[List[int]]
    :rtype: List[bool]
    """
    def check(left1, right1, left2, right2):
        def same(left, right):
            return all(prefixs1[right+1][i]-prefixs1[left][i] == prefixs2[right+1][i]-prefixs2[left][i] for i in xrange(26))

        min_left, max_left = min(left1, left2), max(left1, left2)
        min_right, max_right = min(right1, right2), max(right1, right2)
        if not (prefix[min_left]-prefix[0] == prefix[-1]-prefix[max_right+1] == 0):
            return False
        if min_right < max_left:  # non-overlapped
            return prefix[max_left]-prefix[min_right+1] == 0 and same(min_left, min_right) and same(max_left, max_right)
        # overlapped
        if (left1 == min_left) == (right1 == max_right):  # inside another
            return same(min_left, max_right)
        # not inside another
        p1, p2 = (prefixs1, prefixs2) if min_left == left1 else (prefixs2, prefixs1)
        diff1 = [(p1[min_right+1][i]-p1[min_left][i])-(p2[max_left][i]-p2[min_left][i]) for i in xrange(26)]
        diff2 = [(p2[max_right+1][i]-p2[max_left][i])-(p1[max_right+1][i]-p1[min_right+1][i]) for i in xrange(26)]
        return diff1 == diff2 and all(x >= 0 for x in diff1)  # test case: s = "aabbba", queries = [[0,1,3,4]]

    prefix = [0]*(len(s)//2+1)
    prefixs1 = [[0]*26 for _ in xrange(len(s)//2+1)]
    prefixs2 = [[0]*26 for _ in xrange(len(s)//2+1)]
    for i in xrange(len(s)//2):
        x, y = ord(s[i])-ord('a'), ord(s[~i])-ord('a')
        prefix[i+1] = prefix[i]+int(x != y)
        for j in xrange(26):
            prefixs1[i+1][j] = prefixs1[i][j]+int(j == x)
            prefixs2[i+1][j] = prefixs2[i][j]+int(j == y)
    return [check(q[0], q[1], (len(s)-1)-q[3], (len(s)-1)-q[2]) for q in queries]


