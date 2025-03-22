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

def smallestRepunitDivByK(self, K):
    """
    :type K: int
    :rtype: int
    """
    # by observation, K % 2 = 0 or K % 5 = 0, it is impossible
    if K % 2 == 0 or K % 5 == 0:
        return -1

    # let f(N) is a N-length integer only containing digit 1
    # if there is no N in range (1..K) s.t. f(N) % K = 0
    # => there must be K remainders of f(N) % K in range (1..K-1) excluding 0
    # => due to pigeonhole principle, there must be at least 2 same remainders
    # => there must be some x, y in range (1..K) and x > y s.t. f(x) % K = f(y) % K
    # => (f(x) - f(y)) % K = 0
    # => (f(x-y) * 10^y) % K = 0
    # => due to (x-y) in range (1..K)
    # => f(x-y) % K != 0
    # => 10^y % K = 0
    # => K % 2 = 0 or K % 5 = 0
    # => -><-
    # it proves that there must be some N in range (1..K) s.t. f(N) % K = 0
    result = 0
    for N in xrange(1, K+1):
        result = (result*10+1) % K
        if not result:
            return N
    assert(False)
    return -1  # never reach


