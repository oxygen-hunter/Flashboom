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

def getWinner(self, arr, k):
    """
    :type arr: List[int]
    :type k: int
    :rtype: int
    """
    result = arr[0]
    count = 0
    for i in xrange(1, len(arr)):
        if arr[i] > result:
            result = arr[i]
            count = 0
        count += 1
        if (count == k):
            break
    return result


