def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

def distributeCandies(self, n, limit):
    """
    :type n: int
    :type limit: int
    :rtype: int
    """
    def nCr(n, r):  # Time: O(n), Space: O(1)
        if not 0 <= r <= n:
            return 0
        if n-r < r:
            r = n-r
        c = 1
        for k in xrange(1, r+1):
            c *= n-k+1
            c //= k
        return c
    
    def nHr(n, r):
        return nCr(n+(r-1), r-1)

    R = 3
    return sum((-1 if r%2 else 1) * nCr(R, r) * nHr(n-r*(limit+1), R) for r in xrange(R+1))


