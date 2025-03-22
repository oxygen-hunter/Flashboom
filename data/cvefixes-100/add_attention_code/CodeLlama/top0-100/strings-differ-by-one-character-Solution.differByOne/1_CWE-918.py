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

def differByOne(self, dict):
    """
    :type dict: List[str]
    :rtype: bool
    """
    MOD, P = 10**9+7, 113

    hashes = [0]*len(dict)
    for i, word in enumerate(dict):
        for c in word:
            hashes[i] = (P*hashes[i] + (ord(c)-ord('a'))) % MOD

    base = 1
    for p in reversed(xrange(len(dict[0]))):        
        lookup = collections.defaultdict(list)
        for i, word in enumerate(dict):
            new_hash = (hashes[i] - base*(ord(word[p])-ord('a'))) % MOD
            if new_hash in lookup:
                for j in lookup[new_hash]:
                    if dict[j][:p]+dict[j][p+1:] == word[:p]+word[p+1:]:
                        return True
            lookup[new_hash].append(i)
        base = P*base % MOD
    return False


