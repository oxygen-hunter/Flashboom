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

def numDupDigitsAtMostN(self, N):
    """
    :type N: int
    :rtype: int
    """
    def P(m, n):
        result = 1
        for _ in xrange(n):
            result *= m
            m -= 1
        return result

    digits = map(int, str(N+1))
    result = 0

    # Given 321
    #
    # 1. count numbers without repeated digits:
    # - X
    # - XX
    for i in xrange(1, len(digits)):
        result += P(9, 1)*P(9, i-1)
    
    # 2. count numbers without repeated digits:
    # - 1XX ~ 3XX
    # - 30X ~ 32X
    # - 320 ~ 321
    prefix_set = set()
    for i, x in enumerate(digits):
        for y in xrange(1 if i == 0 else 0, x):
            if y in prefix_set:
                continue
            result += P(9-i, len(digits)-i-1)
        if x in prefix_set:
            break
        prefix_set.add(x)
    return N-result


