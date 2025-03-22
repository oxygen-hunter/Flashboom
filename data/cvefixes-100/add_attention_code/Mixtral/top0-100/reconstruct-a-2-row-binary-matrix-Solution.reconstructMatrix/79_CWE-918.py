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

def reconstructMatrix(self, upper, lower, colsum):
    """
    :type upper: int
    :type lower: int
    :type colsum: List[int]
    :rtype: List[List[int]]
    """
    upper_matrix, lower_matrix = [0]*len(colsum), [0]*len(colsum)
    for i in xrange(len(colsum)):
        upper_matrix[i] = int(upper > 0 and colsum[i] != 0)
        lower_matrix[i] = colsum[i]-upper_matrix[i]
        upper -= upper_matrix[i]
        lower -= lower_matrix[i]
    return [upper_matrix, lower_matrix] if upper == lower == 0 else []


