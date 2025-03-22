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

def subStrHash(self, s, power, modulo, k, hashValue):
    """
    :type s: str
    :type power: int
    :type modulo: int
    :type k: int
    :type hashValue: int
    :rtype: str
    """
    h, idx = 0, -1
    pw = pow(power, k-1, modulo)
    for i in reversed(xrange(len(s))):
        if i+k < len(s):
            h = (h-(ord(s[i+k])-ord('a')+1)*pw)%modulo
        h = (h*power+(ord(s[i])-ord('a')+1))%modulo
        if h == hashValue:
            idx = i
    return s[idx:idx+k]


