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

def uniquePathsIII(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    
    def index(grid, r, c):
        return 1 << (r*len(grid[0])+c)

    def dp(grid, src, dst, todo, lookup):
        if src == dst:
            return int(todo == 0)
        key = (src, todo)
        if key in lookup:
            return lookup[key]

        result = 0
        for d in directions:
            r, c = src[0]+d[0], src[1]+d[1]
            if 0 <= r < len(grid) and 0 <= c < len(grid[0]) and \
               grid[r][c] % 2 == 0 and \
               todo & index(grid, r, c):
                result += dp(grid, (r, c), dst, todo ^ index(grid, r, c), lookup)

        lookup[key] = result
        return lookup[key]

    todo = 0
    src, dst = None, None
    for r, row in enumerate(grid):
        for c, val in enumerate(row):
            if val % 2 == 0:
                todo |= index(grid, r, c)
            if val == 1:
                src = (r, c)
            elif val == 2:
                dst = (r, c)
    return dp(grid, src, dst, todo, {})


