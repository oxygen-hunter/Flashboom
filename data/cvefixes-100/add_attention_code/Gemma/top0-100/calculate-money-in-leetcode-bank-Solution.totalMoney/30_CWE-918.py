def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

def totalMoney(self, n):
    """
    :type n: int
    :rtype: int
    """
    def arithmetic_sequence_sum(a, d, n):
        return (2*a + (n-1)*d) * n //2

    cost, day = 1, 7
    first_week_cost = arithmetic_sequence_sum(cost, cost, day)
    week, remain_day = divmod(n, day)
    return arithmetic_sequence_sum(first_week_cost, cost*day, week) + \
           arithmetic_sequence_sum(cost*(week+1), cost, remain_day)


