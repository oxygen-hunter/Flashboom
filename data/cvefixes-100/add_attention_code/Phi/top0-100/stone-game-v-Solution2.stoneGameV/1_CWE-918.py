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

def stoneGameV(self, stoneValue):
    """
    :type stoneValue: List[int]
    :rtype: int
    """
    n = len(stoneValue)
    prefix = [0]
    for v in stoneValue:
        prefix.append(prefix[-1] + v)

    mid = [[0]*n for _ in xrange(n)]
    for l in xrange(1, n+1):
        for i in xrange(n-l+1):
            j = i+l-1
            p = i if l == 1 else mid[i][j-1]
            while prefix[p]-prefix[i] < prefix[j+1]-prefix[p]:
                p += 1  # Time: O(n^2) in total
            mid[i][j] = p
    
    rmq = [[0]*n for _ in xrange(n)]
    for i in xrange(n):
        rmq[i][i] = stoneValue[i]

    dp = [[0]*n for _ in xrange(n)]
    for l in xrange(2, n+1):
        for i in xrange(n-l+1):
            j = i+l-1
            p = mid[i][j]
            max_score = 0
            if prefix[p]-prefix[i] == prefix[j+1]-prefix[p]:
                max_score = max(rmq[i][p-1], rmq[j][p])
            else:
                if i <= p-2:
                    max_score = max(max_score, rmq[i][p-2])
                if p <= j:
                    max_score = max(max_score, rmq[j][p])
            dp[i][j] = max_score
            rmq[i][j] = max(rmq[i][j-1], (prefix[j+1]-prefix[i]) + max_score)
            rmq[j][i] = max(rmq[j][i+1], (prefix[j+1]-prefix[i]) + max_score)
    return dp[0][n-1]


