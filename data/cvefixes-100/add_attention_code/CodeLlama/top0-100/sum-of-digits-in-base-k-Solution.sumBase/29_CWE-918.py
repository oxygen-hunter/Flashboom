def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

def sumBase(self, n, k):
    """
    :type n: int
    :type k: int
    :rtype: int
    """
    result = 0
    while n:
        n, r = divmod(n, k)
        result += r
    return result


