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

def countEven(self, num):
    """
    :type num: int
    :rtype: int
    """
    def parity(x):
        result = 0
        while x:
            result += x%10
            x //= 10
        return result%2

    return sum(parity(x) == 0 for x in xrange(1, num+1))



