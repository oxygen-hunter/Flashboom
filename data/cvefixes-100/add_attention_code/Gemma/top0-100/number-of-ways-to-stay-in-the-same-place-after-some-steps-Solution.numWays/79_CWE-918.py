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

def numWays(self, steps, arrLen):
    """
    :type steps: int
    :type arrLen: int
    :rtype: int
    """
    MOD = int(1e9+7)
    l = min(1+steps//2, arrLen)
    dp = [0]*(l+2)
    dp[1] = 1
    while steps > 0:
        steps -= 1
        new_dp = [0]*(l+2)
        for i in xrange(1, l+1):
            new_dp[i] = (dp[i] + dp[i-1] + dp[i+1]) % MOD
        dp = new_dp
    return dp[1]


