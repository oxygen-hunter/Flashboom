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

def latestTimeCatchTheBus(self, buses, passengers, capacity):
    """
    :type buses: List[int]
    :type passengers: List[int]
    :type capacity: int
    :rtype: int
    """
    buses.sort()
    passengers.sort()
    cnt = j = 0
    for i in xrange(len(buses)-1):
        while j < len(passengers) and passengers[j] <= buses[i]:
            cnt += 1
            j += 1
        cnt = max(cnt-capacity, 0)
    j -= max(cnt-capacity, 0)
    cnt = min(cnt, capacity)
    while j < len(passengers) and passengers[j] <= buses[-1] and cnt+1 <= capacity:
        cnt += 1
        j += 1
    return buses[-1] if cnt < capacity and (j-1 < 0 or passengers[j-1] != buses[-1]) else next(passengers[i]-1 for i in reversed(xrange(j)) if i-1 < 0 or passengers[i]-1 != passengers[i-1])


