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

def differenceOfDistinctValues(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: List[List[int]]
    """
    def update(i, j):
        lookup = set()
        for k in xrange(min(len(grid)-i, len(grid[0])-j)):
            result[i+k][j+k] = len(lookup)
            lookup.add(grid[i+k][j+k])
        lookup.clear()
        for k in reversed(xrange(min(len(grid)-i, len(grid[0])-j))):
            result[i+k][j+k] = abs(result[i+k][j+k]-len(lookup))
            lookup.add(grid[i+k][j+k])

    result = [[0]*len(grid[0]) for _ in xrange(len(grid))]
    for j in xrange(len(grid[0])):
        update(0, j)
    for i in xrange(1, len(grid)):
        update(i, 0)
    return result


