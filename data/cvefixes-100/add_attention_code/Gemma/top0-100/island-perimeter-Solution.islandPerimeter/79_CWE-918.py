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

def islandPerimeter(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    count, repeat = 0, 0

    for i in xrange(len(grid)):
        for j in xrange(len(grid[i])):
            if grid[i][j] == 1:
                count += 1
                if i != 0 and grid[i - 1][j] == 1:
                    repeat += 1
                if j != 0 and grid[i][j - 1] == 1:
                    repeat += 1

    return 4*count - 2*repeat



