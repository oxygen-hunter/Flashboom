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

def secondMinimum(self, n, edges, time, change):
    """
    :type n: int
    :type edges: List[List[int]]
    :type time: int
    :type change: int
    :rtype: int
    """
    INF = float("inf")
    def bfs(adj, start):
        q = [start]
        dist = [INF]*len(adj)
        dist[start] = 0
        while q:
            new_q = []
            for u in q:
                for v in adj[u]:
                    if dist[v] != INF:
                        continue
                    dist[v] = dist[u]+1
                    new_q.append(v)
            q = new_q
        return dist

    def calc_time(time, change, dist):
        result = 0
        for _ in xrange(dist):
            if result//change%2:
                result = (result//change+1)*change
            result += time
        return result

    adj = [[] for _ in xrange(n)]
    for u, v in edges:
        adj[u-1].append(v-1)
        adj[v-1].append(u-1)
    dist_to_end, dist_to_start = bfs(adj, 0), bfs(adj, n-1)

    dist = dist_to_end[n-1]+2  # always exists
    for i in xrange(n):  # case of detour
        if dist_to_end[i]+dist_to_start[i] == dist_to_end[n-1]:
            continue
        dist = min(dist, dist_to_end[i]+dist_to_start[i])  # find second min
        if dist == dist_to_end[n-1]+1:
            break
    return calc_time(time, change, dist)


