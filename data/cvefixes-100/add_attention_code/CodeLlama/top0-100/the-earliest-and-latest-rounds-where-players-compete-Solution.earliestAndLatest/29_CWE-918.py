def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

def earliestAndLatest(self, n, firstPlayer, secondPlayer):
    """
    :type n: int
    :type firstPlayer: int
    :type secondPlayer: int
    :rtype: List[int]
    """
    def memoization(t, l, r, lookup):
        # t: total number of players,
        # l: number of players left to the nearest top2 player,
        # r: number of players right to the nearest top2 player
        if (t, l, r) not in lookup:
            if l == r:
                return (1, 1)
            if l > r:  # make sure l <= r
                l, r, = r, l
            result = [float("inf"), 0]
            for i in xrange(l+1):
                l_win_cnt, l_lose_cnt, nt, pair_cnt = i+1, l-i, (t+1)//2, t//2
                min_j = max(l_lose_cnt, r-(pair_cnt-l_lose_cnt))  # j >= l_lose_cnt and j >= r-(pair_cnt-l_lose_cnt)
                max_j = min(r-l_win_cnt, (nt-l_win_cnt)-1)  # j <= r-l_win_cnt and j <= (nt-l_win_cnt)-1
                for j in xrange(min_j, max_j+1):
                    tmp = memoization(nt, i, j, lookup)
                    result = min(result[0], tmp[0]+1), max(result[1], tmp[1]+1)
            lookup[t, l, r] = result
        return lookup[t, l, r]
    
    return memoization(n, firstPlayer-1, n-secondPlayer, {})


