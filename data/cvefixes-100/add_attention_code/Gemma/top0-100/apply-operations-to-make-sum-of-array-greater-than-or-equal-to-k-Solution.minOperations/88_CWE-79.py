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

def minOperations(self, k):
    """
    :type k: int
    :rtype: int
    """
    # reference: https://stackoverflow.com/questions/15390807/integer-square-root-in-python
    def isqrt(n):
        a, b = n, (n+1)//2
        while b < a:
            a, b = b, (b+n//b)//2
        return a

    def ceil_divide(a, b):
        return (a+b-1)//b

    x = isqrt(k)
    return (x-1)+(ceil_divide(k, x)-1)


