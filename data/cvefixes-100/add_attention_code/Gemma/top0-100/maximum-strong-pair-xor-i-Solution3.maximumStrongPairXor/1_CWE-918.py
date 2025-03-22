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

def maximumStrongPairXor(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    result = 0
    for i in reversed(xrange(max(nums).bit_length())):
        prefix_min, prefix_max = {}, {}
        for x in nums:
            y = x>>i
            if y not in prefix_min:
                prefix_min[y] = prefix_max[y] = x
            prefix_min[y] = min(prefix_min[y], x)
            prefix_max[y] = max(prefix_max[y], x)
        result <<= 1
        for x in prefix_min.iterkeys():
            y = (result|1)^x
            assert(x != y)
            if y in prefix_max and prefix_min[max(x, y)] <= 2*prefix_max[min(x, y)]:
                result |= 1
                break
    return result



