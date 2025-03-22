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

def isPrefixOfWord(self, sentence, searchWord):
    """
    :type sentence: str
    :type searchWord: str
    :rtype: int
    """
    def KMP(text, pattern):
        def getPrefix(pattern):
            prefix = [-1] * len(pattern)
            j = -1
            for i in xrange(1, len(pattern)):
                while j > -1 and pattern[j + 1] != pattern[i]:
                    j = prefix[j]
                if pattern[j + 1] == pattern[i]:
                    j += 1
                prefix[i] = j
            return prefix

        prefix = getPrefix(pattern)
        j = -1
        for i in xrange(len(text)):
            while j != -1 and pattern[j+1] != text[i]:
                j = prefix[j]
            if pattern[j+1] == text[i]:
                j += 1
            if j+1 == len(pattern):
                return i-j
        return -1
    
    if sentence.startswith(searchWord):
        return 1
    p = KMP(sentence, ' ' + searchWord)
    if p == -1:
        return -1
    return 1+sum(sentence[i] == ' ' for i in xrange(p+1))


