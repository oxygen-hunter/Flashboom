def _check_login_status(self, request: Request) -> LoginButton:
    # Each time the page is refreshed or loaded, check if the user is logged in and adapt label
    session = getattr(request, "session", None) or getattr(
        request.request, "session", None
    )
    if session is None or "oauth_info" not in session:
        return LoginButton(value=self.value, interactive=True)
    else:
        username = session["oauth_info"]["userinfo"]["preferred_username"]
        logout_text = self.logout_value.format(username)
        return LoginButton(logout_text, interactive=True)

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


