def profile():
    languages = calibre_db.speaking_language()
    translations = babel.list_translations() + [LC('en')]
    kobo_support = feature_support['kobo'] and config.config_kobo_sync
    if feature_support['oauth'] and config.config_login_type == 2:
        oauth_status = get_oauth_status()
        local_oauth_check = oauth_check
    else:
        oauth_status = None
        local_oauth_check = {}

    if request.method == "POST":
        change_profile(kobo_support, local_oauth_check, oauth_status, translations, languages)
    return render_title_template("user_edit.html",
                                 translations=translations,
                                 profile=1,
                                 languages=languages,
                                 content=current_user,
                                 kobo_support=kobo_support,
                                 title=_(u"%(name)s's profile", name=current_user.name),
                                 page="me",
                                 registered_oauth=local_oauth_check,
                                 oauth_status=oauth_status)

def count(self, num1, num2, min_sum, max_sum):
    """
    :type num1: str
    :type num2: str
    :type min_sum: int
    :type max_sum: int
    :rtype: int
    """
    MOD = 10**9+7
    def f(x):
        dp = [[0]*(max_sum+1) for _ in xrange(2)]
        dp[0][0] = dp[1][0] = 1
        for i in reversed(xrange(len(x))):
            new_dp = [[0]*(max_sum+1) for _ in xrange(2)]
            for t in xrange(2):
                for total in xrange(max_sum+1):
                    for d in xrange(min((int(x[i]) if t else 9), total)+1):
                        new_dp[t][total] = (new_dp[t][total]+dp[int(t and d == int(x[i]))][total-d])%MOD
            dp = new_dp
        return reduce(lambda x, y: (x+y)%MOD, (dp[1][total] for total in xrange(min_sum, max_sum+1)))

    return (f(num2)-f(str(int(num1)-1)))%MOD


