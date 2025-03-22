def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

def singleDivisorTriplet(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    def check(a, b, c):
        return sum((a+b+c)%x == 0 for x in (a, b, c)) == 1

    cnt = collections.Counter(nums)
    return 6*(sum(cnt[a]*cnt[b]*cnt[c] for a, b, c in itertools.combinations(cnt.keys(), 3) if check(a, b, c)) +
              sum(cnt[a]*(cnt[a]-1)//2*cnt[b] for a, b in itertools.permutations(cnt.keys(), 2) if check(a, a, b)))


