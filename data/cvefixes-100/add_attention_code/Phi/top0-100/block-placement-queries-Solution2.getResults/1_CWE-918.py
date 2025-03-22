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

def getResults(self, queries):
    """
    :type queries: List[List[int]]
    :rtype: List[bool]
    """
    # Template:
    # https://github.com/kamyu104/LeetCode-Solutions/blob/master/Python/booking-concert-tickets-in-groups.py
    class SegmentTree(object):
        def __init__(self, N,
                    build_fn=lambda _: None,
                    query_fn=lambda x, y: y if x is None else x if y is None else max(x, y),
                    update_fn=lambda x: x):
            self.tree = [None]*(1<<((N-1).bit_length()+1))
            self.base = len(self.tree)>>1
            self.query_fn = query_fn
            self.update_fn = update_fn
            for i in xrange(self.base, self.base+N):
                self.tree[i] = build_fn(i-self.base)
            for i in reversed(xrange(1, self.base)):
                self.tree[i] = query_fn(self.tree[i<<1], self.tree[(i<<1)+1])

        def update(self, i, h):
            x = self.base+i
            self.tree[x] = self.update_fn(h)
            while x > 1:
                x >>= 1
                self.tree[x] = self.query_fn(self.tree[x<<1], self.tree[(x<<1)+1])

        def query(self, L, R):
            L += self.base
            R += self.base
            left = right = None
            while L <= R:
                if L & 1:
                    left = self.query_fn(left, self.tree[L])
                    L += 1
                if R & 1 == 0:
                    right = self.query_fn(self.tree[R], right)
                    R -= 1
                L >>= 1
                R >>= 1
            return self.query_fn(left, right)

    def update(x):
        sl.add(x)
        i = sl.bisect_left(x)
        st.update(val_to_idx[x], x-(sl[i-1] if i-1 >= 0 else 0))
        if i+1 < len(sl):
            st.update(val_to_idx[sl[i+1]], sl[i+1]-x)
        
    val_to_idx = {x:i for i, x in enumerate(sorted(q[1] for q in queries if q[0] == 1))}
    st = SegmentTree(len(val_to_idx))
    sl = SortedList()
    result = []
    for q in queries:
        if q[0] == 1:
            update(q[1])
        else:
            i = sl.bisect_left(q[1])
            result.append(q[1]-(sl[i-1] if i-1 >= 0 else 0) >= q[2] or (i-1 >= 0 and st.query(0, val_to_idx[sl[i-1]]) >= q[2]))
    return result


