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

def closeStrings(self, word1, word2):
    """
    :type word1: str
    :type word2: str
    :rtype: bool
    """
    if len(word1) != len(word2):
        return False 
    
    cnt1, cnt2 = collections.Counter(word1), collections.Counter(word2)   # Reuse of keys
    return set(cnt1.iterkeys()) == set(cnt2.iterkeys()) and \
           collections.Counter(cnt1.itervalues()) == collections.Counter(cnt2.itervalues())


