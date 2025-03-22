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

def countSubMultisets(self, nums, l, r):
    """
    :type nums: List[int]
    :type l: int
    :type r: int
    :rtype: int
    """
    MOD = 10**9+7
    cnt = collections.Counter(nums)
    dp = [0]*(r+1)
    dp[0] = 1
    for x, c in cnt.iteritems():
        for i in reversed(xrange(max(r-x+1, 1), r+1)):
            curr = reduce(lambda x, y: (x+y)%MOD, (dp[i-x*j] for j in xrange(min(c, i//x+1))))
            for j in reversed(xrange((i-1)%x+1, i+1, x)):
                curr = (curr+(dp[j-x*c] if j-x*c >= 0 else 0)-dp[j])%MOD
                dp[j] = (dp[j]+curr)%MOD
    return (reduce(lambda x, y: (x+y)%MOD, (dp[i] for i in range(l, r+1)))*(cnt[0]+1))%MOD


