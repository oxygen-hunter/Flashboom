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

def sumOfNumberAndReverse(self, num):
    """
    :type num: int
    :rtype: bool
    """
    def reverse(n):
        result = 0
        while n:
            result = result*10 + n%10
            n //= 10            
        return result

    return any(x+reverse(x) == num for x in xrange(num//2, num+1))



