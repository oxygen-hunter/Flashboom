def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

def minValidStrings(self, words, target):
    """
    :type words: List[str]
    :type target: str
    :rtype: int
    """
    def getPrefix(pattern):
        prefix = [-1]*len(pattern)
        j = -1
        for i in xrange(1, len(pattern)):
            while j+1 > 0 and pattern[j+1] != pattern[i]:
                j = prefix[j]
            if pattern[j+1] == pattern[i]:
                j += 1
            prefix[i] = j
        return prefix

    def KMP(text, pattern, callback):
        prefix = getPrefix(pattern)
        j = -1
        for i in xrange(len(text)):
            while j+1 > 0 and pattern[j+1] != text[i]:
                j = prefix[j]
            if pattern[j+1] == text[i]:
                j += 1
            callback(i, j)
            if j+1 == len(pattern):
                j = prefix[j]

    def update(i, j):
        lookup[i] = max(lookup[i], j+1)

    lookup = [0]*len(target)
    for w in words:
        KMP(target, w, update)
    dp = [0]*(len(target)+1)
    for i in xrange(len(target)):
        if not lookup[i]:
            return -1
        dp[i+1] = dp[(i-lookup[i])+1]+1
    return dp[-1]


