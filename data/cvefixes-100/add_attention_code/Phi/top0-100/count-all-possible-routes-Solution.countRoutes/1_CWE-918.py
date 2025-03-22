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

def countRoutes(self, locations, start, finish, fuel):
    """
    :type locations: List[int]
    :type start: int
    :type finish: int
    :type fuel: int
    :rtype: int
    """
    MOD = 10**9+7

    s, f = locations[start], locations[finish]
    locations.sort()
    start, finish = bisect.bisect_left(locations, s), bisect.bisect_left(locations, f)

    left = [[0]*(fuel+1) for _ in xrange(len(locations))]  # left[i][f], last move is toward left to location i by f fuel
    right = [[0]*(fuel+1) for _ in xrange(len(locations))]  # right[i][f], last move is toward right to location i by f fuel
    for f in xrange(1, fuel+1):
        for j in xrange(len(locations)-1):
            d = locations[j+1]-locations[j]
            if f > d:
                # left[j][f] = right[j+1][f-d(j, j+1)] + 2*right[j+2][f-d(j, j+2)] + ... + 2^(k-1)*right[j+k][f-d(j, j+k)]
                # => left[j+1][f] = (ight[j+2][f-d(j+1, j+2)] + 2*right[j+3][f-d(j+1, j+3)] + ... + 2^(k-2)*right[j+1+k-1][f-d(j+1, j+1+k-1)]
                # => left[j+1][f-d(j, j+1)] = right[j+2][f-d(j, j+2)] + 2*right[j+3][f-d(j, j+3)] + ... + 2^(k-2)*right[j+k][f-d(j, j+k)]
                # => left[j][f] = right[j+1][f-d(j, j+1)] + 2*left[j+1][f-d(j, j+1)]
                left[j][f] = (right[j+1][f-d] + 2*left[j+1][f-d] % MOD) % MOD
            elif f == d:
                left[j][f] = int(j+1 == start)
        for j in xrange(1, len(locations)):
            d = locations[j]-locations[j-1]
            if f > d:
                # right[j][f] = left[j-1][f-d(j, j-1)] + 2*left[j-2][f-d(j, j-2)] + ... + 2^(k-1)*left[j-k][f-d(j, j-k)]
                # => right[j-1][f] = left[j-2][f-d(j-1, j-2)] + 2*left[j-3][f-d(j-1, j-3)] + ... + 2^(k-2)*left[j-1-k+1][f-d(j-1, j-1-k+1)]
                # => right[j-1][f-d(j, j-1)] = left[j-2][f-d(j, j-2)] + 2*left[j-3][f-d(j, j-3)] + ... + 2^(k-2)*left[j-k][f-d(j, j-k)]
                # => right[j][f] = left[j-1][f-d(j, j-1)] + 2*right[j-1][f-d(j, j-1)]
                right[j][f] = (left[j-1][f-d] + 2*right[j-1][f-d] % MOD) % MOD
            elif f == d:
                right[j][f] = int(j-1 == start)
    result = int(start == finish)
    for f in xrange(1, fuel+1):
        result = ((result + left[finish][f]) % MOD + right[finish][f]) % MOD
    return result



