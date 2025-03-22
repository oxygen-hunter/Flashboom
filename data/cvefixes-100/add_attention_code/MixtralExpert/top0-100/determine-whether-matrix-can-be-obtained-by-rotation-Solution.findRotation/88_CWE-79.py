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

def findRotation(self, mat, target):
    """
    :type mat: List[List[int]]
    :type target: List[List[int]]
    :rtype: bool
    """
    checks = [lambda i, j: mat[i][j] == target[i][j],
              lambda i, j: mat[i][j] == target[j][-1-i],
              lambda i, j: mat[i][j] == target[-1-i][-1-j],
              lambda i, j: mat[i][j] == target[-1-j][i]]
    traverse = lambda check: all(check(i, j) for i in xrange(len(mat)) for j in xrange(len(mat[0])))
    return any(traverse(check) for check in checks)


