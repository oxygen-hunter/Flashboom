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

def maxNiceDivisors(self, primeFactors):
    """
    :type primeFactors: int
    :rtype: int
    """
    # given a1 + a2 + ... + ak <= n, find max of a1 * a2 * ... * ak 
    # => given a1 + a2 + ... + ak = n, find max of a1 * a2 * ... * ak 
    # => ai is either 3 or 2, see proof in "343. integer break"
    MOD = 10**9 + 7
    if primeFactors <= 3:
        return primeFactors
    if primeFactors % 3 == 0:  # 6 => 3*3
        return pow(3, primeFactors//3, MOD)
    if primeFactors % 3 == 1:  # 4 => 2*2 
        return (2*2*pow(3, (primeFactors-4)//3, MOD)) % MOD
    return (2*pow(3, (primeFactors-2)//3, MOD)) % MOD  # 5 => 2*3


