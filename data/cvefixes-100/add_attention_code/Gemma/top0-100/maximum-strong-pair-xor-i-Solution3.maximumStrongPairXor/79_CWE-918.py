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

def maximumStrongPairXor(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    result = 0
    for i in reversed(xrange(max(nums).bit_length())):
        prefix_min, prefix_max = {}, {}
        for x in nums:
            y = x>>i
            if y not in prefix_min:
                prefix_min[y] = prefix_max[y] = x
            prefix_min[y] = min(prefix_min[y], x)
            prefix_max[y] = max(prefix_max[y], x)
        result <<= 1
        for x in prefix_min.iterkeys():
            y = (result|1)^x
            assert(x != y)
            if y in prefix_max and prefix_min[max(x, y)] <= 2*prefix_max[min(x, y)]:
                result |= 1
                break
    return result



