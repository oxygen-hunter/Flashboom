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

def calculate(self, s):
    operands, operators = [], []
    operand = ""
    for i in reversed(xrange(len(s))):
        if s[i].isdigit():
            operand += s[i]
            if i == 0 or not s[i-1].isdigit():
                operands.append(int(operand[::-1]))
                operand = ""
        elif s[i] == ')' or s[i] == '+' or s[i] == '-':
            operators.append(s[i])
        elif s[i] == '(':
            while operators[-1] != ')':
                self.compute(operands, operators)
            operators.pop()

    while operators:
        self.compute(operands, operators)

    return operands[-1]



