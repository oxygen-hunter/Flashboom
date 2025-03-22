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

def shortestBridge(self, A):
    """
    :type A: List[List[int]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    def get_islands(A):
        islands = []
        done = set()
        for r, row in enumerate(A):
            for c, val in enumerate(row):
                if val == 0 or (r, c) in done:
                    continue
                s = [(r, c)]
                lookup = set(s)
                while s:
                    node = s.pop()
                    for d in directions:
                        nei = node[0]+d[0], node[1]+d[1]
                        if not (0 <= nei[0] < len(A) and 0 <= nei[1] < len(A[0])) or \
                           nei in lookup or A[nei[0]][nei[1]] == 0:
                            continue
                        s.append(nei)
                        lookup.add(nei)
                done |= lookup
                islands.append(lookup)
                if len(islands) == 2:
                    break
        return islands

    lookup, target = get_islands(A)
    q = collections.deque([(node, 0) for node in lookup])
    while q:
        node, dis = q.popleft()
        if node in target:
            return dis-1
        for d in directions:
            nei = node[0]+d[0], node[1]+d[1]
            if not (0 <= nei[0] < len(A) and 0 <= nei[1] < len(A[0])) or \
               nei in lookup:
                continue
            q.append((nei, dis+1))
            lookup.add(nei)


