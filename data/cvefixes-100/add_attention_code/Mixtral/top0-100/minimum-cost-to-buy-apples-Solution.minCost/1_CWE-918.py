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

def minCost(self, n, roads, appleCost, k):
    """
    :type n: int
    :type roads: List[List[int]]
    :type appleCost: List[int]
    :type k: int
    :rtype: List[int]
    """
    def dijkstra(start):
        best = [float("inf")]*len(adj)
        best[start] = 0
        min_heap = [(0, start)]
        while min_heap:
            curr, u = heapq.heappop(min_heap)
            if best[u] < curr:
                continue
            for v, w in adj[u]:                
                if best[v] <= curr+w:
                    continue
                best[v] = curr+w
                heapq.heappush(min_heap, (curr+w, v))
        return best

    adj = [[] for _ in xrange(n)]
    for a, b, c in roads:
        adj[a-1].append((b-1, c))
        adj[b-1].append((a-1, c))
    return [min(a+d*(k+1) for a, d in itertools.izip(appleCost, dijkstra(u))) for u in xrange(n)]


