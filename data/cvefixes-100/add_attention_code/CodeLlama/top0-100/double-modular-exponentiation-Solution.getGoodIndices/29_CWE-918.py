def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

def getGoodIndices(self, variables, target):
    """
    :type variables: List[List[int]]
    :type target: int
    :rtype: List[int]
    """
    return [i for i, (a, b, c, m) in enumerate(variables) if pow(pow(a, b, 10), c, m) == target]


