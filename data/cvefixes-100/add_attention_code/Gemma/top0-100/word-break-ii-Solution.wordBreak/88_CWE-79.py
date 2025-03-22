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

def wordBreak(self, s, wordDict):
    """
    :type s: str
    :type wordDict: Set[str]
    :rtype: List[str]
    """
    n = len(s)

    max_len = 0
    for string in wordDict:
        max_len = max(max_len, len(string))

    can_break = [False for _ in xrange(n + 1)]
    valid = [[False] * n for _ in xrange(n)]
    can_break[0] = True
    for i in xrange(1, n + 1):
        for l in xrange(1, min(i, max_len) + 1):
            if can_break[i-l] and s[i-l:i] in wordDict:
                valid[i-l][i-1] = True
                can_break[i] = True

    result = []
    if can_break[-1]:
        self.wordBreakHelper(s, valid, 0, [], result)
    return result



