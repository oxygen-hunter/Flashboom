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

def kthSmallestPath(self, destination, k):
    """
    :type destination: List[int]
    :type k: int
    :rtype: str
    """
    def nCr(n, r):  # Time: O(n), Space: O(1)
        if n < r:
            return 0
        if n-r < r:
            return nCr(n, n-r)
        c = 1
        for k in xrange(1, r+1):
            c *= n-k+1
            c //= k
        return c

    r, c = destination        
    result = []
    while r+c:
        count = nCr(r+(c-1), r)  # the number of HX..X combinations
        if k <= count:  # the kth instruction is one of HX..X combinations, so go right
            c -= 1
            result.append('H')
        else:  # the kth instruction is one of VX..X combinations, so go down
            k -= count  # the kth one of XX..X combinations is the (k-count)th one of VX..X combinations
            r -= 1
            result.append('V')
    return "".join(result)


