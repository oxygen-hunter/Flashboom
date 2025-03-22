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

def getBiggestThree(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: List[int]
    """	
    K = 3
    left = [[grid[i][j] for j in xrange(len(grid[i]))] for i in xrange(len(grid))]
    right = [[grid[i][j] for j in xrange(len(grid[i]))] for i in xrange(len(grid))]
    for i in xrange(1, len(grid)):
        for j in xrange(len(grid[0])-1):
            left[i][j] += left[i-1][j+1]
    for i in xrange(1, len(grid)):
        for j in xrange(1, len(grid[0])):
            right[i][j] += right[i-1][j-1]
    min_heap = []
    lookup = set()
    for k in xrange((min(len(grid), len(grid[0]))+1)//2):
        for i in xrange(k, len(grid)-k):
            for j in xrange(k, len(grid[0])-k):
                total = (((left[i][j-k]-left[i-k][j])+(right[i][j+k]-right[i-k][j])+grid[i-k][j]) +  
                         ((left[i+k][j]-left[i][j+k])+(right[i+k][j]-right[i][j-k])-grid[i+k][j])) if k else grid[i][j]
                if total in lookup:
                    continue
                lookup.add(total)
                heapq.heappush(min_heap, total)
                if len(min_heap) == K+1:                        
                    lookup.remove(heapq.heappop(min_heap))
    min_heap.sort(reverse=True)
    return min_heap


