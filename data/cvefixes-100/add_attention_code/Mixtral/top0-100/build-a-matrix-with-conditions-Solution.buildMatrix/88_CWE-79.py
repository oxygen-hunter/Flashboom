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

def buildMatrix(self, k, rowConditions, colConditions):
    """
    :type k: int
    :type rowConditions: List[List[int]]
    :type colConditions: List[List[int]]
    :rtype: List[List[int]]
    """
    def topological_sort(conditions):
        adj = [[] for _ in xrange(k)]
        in_degree = [0]*k
        for u, v in conditions:
            u -= 1
            v -= 1
            adj[u].append(v)
            in_degree[v] += 1
        result = []
        q = [u for u in xrange(k) if not in_degree[u]]
        while q:
            new_q = []
            for u in q:
                result.append(u)
                for v in adj[u]:
                    in_degree[v] -= 1
                    if in_degree[v]:
                        continue
                    new_q.append(v)
            q = new_q
        return result

    row_order = topological_sort(rowConditions)
    if len(row_order) != k:
        return []
    col_order = topological_sort(colConditions)
    if len(col_order) != k:
        return []
    row_idx = {x:i for i, x in enumerate(row_order)}
    col_idx = {x:i for i, x in enumerate(col_order)}
    result = [[0]*k for _ in xrange(k)]
    for i in xrange(k):
        result[row_idx[i]][col_idx[i]] = i+1
    return result


