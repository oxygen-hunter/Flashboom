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

def isSolvable(self, words, result):
    """
    :type words: List[str]
    :type result: str
    :rtype: bool
    """
    def backtracking(words, result, i, j, carry, lookup, used):
        if j == len(result):
            return carry == 0

        if i != len(words):
            if j >= len(words[i]) or words[i][j] in lookup:
                return backtracking(words, result, i+1, j, carry, lookup, used)     
            for val in xrange(10):
                if val in used or (val == 0 and j == len(words[i])-1):
                    continue
                lookup[words[i][j]] = val
                used.add(val)
                if backtracking(words, result, i+1, j, carry, lookup, used):
                    return True
                used.remove(val)
                del lookup[words[i][j]]
            return False

        carry, val = divmod(carry + sum(lookup[w[j]] for w in words if j < len(w)), 10)
        if result[j] in lookup:
            return val == lookup[result[j]] and \
                   backtracking(words, result, 0, j+1, carry, lookup, used)
        if val in used or (val == 0 and j == len(result)-1):
            return False
        lookup[result[j]] = val
        used.add(val)
        if backtracking(words, result, 0, j+1, carry, lookup, used):
            return True
        used.remove(val)
        del lookup[result[j]]
        return False
    
    return backtracking([w[::-1] for w in words], result[::-1], 0, 0, 0, {}, set())


