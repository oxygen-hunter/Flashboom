def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

def minimumTimeToInitialState(self, word, k):
    """
    :type word: str
    :type k: int
    :rtype: int
    """
    def ceil_divide(a, b):
        return (a+b-1)//b

    def z_function(s):  # Time: O(n), Space: O(n)
        z = [0]*len(s)
        l, r = 0, 0
        for i in xrange(1, len(z)):
            if i <= r:
                z[i] = min(r-i+1, z[i-l])
            while i+z[i] < len(z) and s[z[i]] == s[i+z[i]]:
                z[i] += 1
            if i+z[i]-1 > r:
                l, r = i, i+z[i]-1
        return z

    z = z_function(word)
    for i in xrange(k, len(word), k):
        if z[i] == len(word)-i:
            return i//k
    return ceil_divide(len(word), k)


