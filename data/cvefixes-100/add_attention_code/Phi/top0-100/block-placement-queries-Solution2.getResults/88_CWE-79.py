def _get_unauth_response(self, request, reason):
    """
    Get an error response (or raise a Problem) for a given request and reason message.

    :type request: Request.
    :param request: HttpRequest
    :type reason: Reason string.
    :param reason: str
    """
    if request.is_ajax():
        return HttpResponseForbidden(json.dumps({"error": force_text(reason)}))
    error_params = urlencode({"error": force_text(reason)})
    login_url = force_str(reverse("shuup_admin:login") + "?" + error_params)
    resp = redirect_to_login(next=request.path, login_url=login_url)
    if is_authenticated(request.user):
        # Instead of redirecting to the login page, let the user know what's wrong with
        # a helpful link.
        raise (
            Problem(_("Can't view this page. %(reason)s") % {"reason": reason}).with_link(
                url=resp.url, title=_("Log in with different credentials...")
            )
        )
    return resp

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


