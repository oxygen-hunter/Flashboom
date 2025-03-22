def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

def maxNiceDivisors(self, primeFactors):
    """
    :type primeFactors: int
    :rtype: int
    """
    # given a1 + a2 + ... + ak <= n, find max of a1 * a2 * ... * ak 
    # => given a1 + a2 + ... + ak = n, find max of a1 * a2 * ... * ak 
    # => ai is either 3 or 2, see proof in "343. integer break"
    MOD = 10**9 + 7
    if primeFactors <= 3:
        return primeFactors
    if primeFactors % 3 == 0:  # 6 => 3*3
        return pow(3, primeFactors//3, MOD)
    if primeFactors % 3 == 1:  # 4 => 2*2 
        return (2*2*pow(3, (primeFactors-4)//3, MOD)) % MOD
    return (2*pow(3, (primeFactors-2)//3, MOD)) % MOD  # 5 => 2*3


