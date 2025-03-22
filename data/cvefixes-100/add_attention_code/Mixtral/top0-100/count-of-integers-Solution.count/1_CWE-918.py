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

def count(self, num1, num2, min_sum, max_sum):
    """
    :type num1: str
    :type num2: str
    :type min_sum: int
    :type max_sum: int
    :rtype: int
    """
    MOD = 10**9+7
    def f(x):
        dp = [[0]*(max_sum+1) for _ in xrange(2)]
        dp[0][0] = dp[1][0] = 1
        for i in reversed(xrange(len(x))):
            new_dp = [[0]*(max_sum+1) for _ in xrange(2)]
            for t in xrange(2):
                for total in xrange(max_sum+1):
                    for d in xrange(min((int(x[i]) if t else 9), total)+1):
                        new_dp[t][total] = (new_dp[t][total]+dp[int(t and d == int(x[i]))][total-d])%MOD
            dp = new_dp
        return reduce(lambda x, y: (x+y)%MOD, (dp[1][total] for total in xrange(min_sum, max_sum+1)))

    return (f(num2)-f(str(int(num1)-1)))%MOD


