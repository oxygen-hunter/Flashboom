def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

def numDupDigitsAtMostN(self, N):
    """
    :type N: int
    :rtype: int
    """
    def P(m, n):
        result = 1
        for _ in xrange(n):
            result *= m
            m -= 1
        return result

    digits = map(int, str(N+1))
    result = 0

    # Given 321
    #
    # 1. count numbers without repeated digits:
    # - X
    # - XX
    for i in xrange(1, len(digits)):
        result += P(9, 1)*P(9, i-1)
    
    # 2. count numbers without repeated digits:
    # - 1XX ~ 3XX
    # - 30X ~ 32X
    # - 320 ~ 321
    prefix_set = set()
    for i, x in enumerate(digits):
        for y in xrange(1 if i == 0 else 0, x):
            if y in prefix_set:
                continue
            result += P(9-i, len(digits)-i-1)
        if x in prefix_set:
            break
        prefix_set.add(x)
    return N-result


