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

def partitionDisjoint(self, A):
    """
    :type A: List[int]
    :rtype: int
    """
    B = A[:]
    for i in reversed(xrange(len(A)-1)):
        B[i] = min(B[i], B[i+1])
    p_max = 0
    for i in xrange(1, len(A)):
        p_max = max(p_max, A[i-1])
        if p_max <= B[i]:
            return i



