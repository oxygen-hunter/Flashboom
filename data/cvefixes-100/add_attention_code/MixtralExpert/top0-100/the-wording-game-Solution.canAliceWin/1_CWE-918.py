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

def canAliceWin(self, a, b):
    """
    :type a: List[str]
    :type b: List[str]
    :rtype: bool
    """
    def is_closely_greater(a, b):
        return ord(a[0])-ord(b[0]) <= 1 and a > b

    result = True
    i, j = 0, -1
    for _ in xrange(len({w[0] for w in a})+len({w[0] for w in b})):  # each player takes turns using a word with a different first letter than the last word he played
        j = next((j for j in xrange(j+1, len(b)) if is_closely_greater(b[j], a[i])), len(b))
        if j == len(b):
            break
        while j+1 < len(b) and b[j+1][0] == b[j][0]:  # play the lexicographically greatest word with the same first letter
            j += 1
        a, b, i, j, result = b, a, j, i, not result
    return result


