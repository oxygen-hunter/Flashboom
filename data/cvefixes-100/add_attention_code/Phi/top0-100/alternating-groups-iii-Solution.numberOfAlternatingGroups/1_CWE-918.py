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

def numberOfAlternatingGroups(self, colors, queries):
    """
    :type colors: List[int]
    :type queries: List[List[int]]
    :rtype: List[int]
    """
    class BIT(object):  # 0-indexed.
        def __init__(self, n):
            self.__bit = [0]*(n+1)

        def add(self, i, val):
            i += 1
            while i < len(self.__bit):
                self.__bit[i] += val
                i += (i & -i)

        def query(self, i):
            i += 1
            ret = 0
            while i > 0:
                ret += self.__bit[i]
                i -= (i & -i)
            return ret

    def update(i, d):
        if d == +1:
            sl.add(i)
            if len(sl) == 1:
                bit1.add(n, +1)
                bit2.add(n, +n)
        curr = sl.index(i)
        prv, nxt = (curr-1)%len(sl), (curr+1)%len(sl)
        if len(sl) != 1:
            l = (sl[nxt]-sl[prv]-1)%n+1
            bit1.add(l, d*(-1))
            bit2.add(l, d*(-l))
            l = (sl[curr]-sl[prv])%n
            bit1.add(l, d*(+1))
            bit2.add(l, d*(+l))
            l = (sl[nxt]-sl[curr])%n
            bit1.add(l, d*(+1))
            bit2.add(l, d*(+l))
        if d == -1:
            if len(sl) == 1:
                bit1.add(n, -1)
                bit2.add(n, -n)
            sl.pop(curr)

    n = len(colors)
    sl = SortedList()
    bit1, bit2 = BIT(n+1), BIT(n+1)
    for i in xrange(n):
        if colors[i] == colors[(i+1)%n]:
            update(i, +1)
    result = []
    for q in queries:
        if q[0] == 1:
            l = q[1]
            result.append((bit2.query(n)-bit2.query(l-1))-
                          (l-1)*(bit1.query(n)-bit1.query(l-1)) if sl else n)
            continue
        _, i, c = q
        if colors[i] == c:
            continue      
        colors[i] = c          
        update((i-1)%n, +1 if colors[i] == colors[(i-1)%n] else -1) 
        update(i, +1 if colors[i] == colors[(i+1)%n] else -1)
    return result


