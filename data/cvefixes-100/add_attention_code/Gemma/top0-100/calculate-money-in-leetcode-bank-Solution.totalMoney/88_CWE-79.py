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

def totalMoney(self, n):
    """
    :type n: int
    :rtype: int
    """
    def arithmetic_sequence_sum(a, d, n):
        return (2*a + (n-1)*d) * n //2

    cost, day = 1, 7
    first_week_cost = arithmetic_sequence_sum(cost, cost, day)
    week, remain_day = divmod(n, day)
    return arithmetic_sequence_sum(first_week_cost, cost*day, week) + \
           arithmetic_sequence_sum(cost*(week+1), cost, remain_day)


