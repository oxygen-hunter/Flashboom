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

def majorityElement(self, nums):
    """
    :type nums: List[int]
    :rtype: List[int]
    """
    k, n, cnts = 3, len(nums), collections.defaultdict(int)

    for i in nums:
        cnts[i] += 1
        # Detecting k items in cnts, at least one of them must have exactly
        # one in it. We will discard those k items by one for each.
        # This action keeps the same mojority numbers in the remaining numbers.
        # Because if x / n  > 1 / k is true, then (x - 1) / (n - k) > 1 / k is also true.
        if len(cnts) == k:
            for j in cnts.keys():
                cnts[j] -= 1
                if cnts[j] == 0:
                    del cnts[j]

    # Resets cnts for the following counting.
    for i in cnts.keys():
        cnts[i] = 0

    # Counts the occurrence of each candidate integer.
    for i in nums:
        if i in cnts:
            cnts[i] += 1

    # Selects the integer which occurs > [n / k] times.
    result = []
    for i in cnts.keys():
        if cnts[i] > n / k:
            result.append(i)

    return result



