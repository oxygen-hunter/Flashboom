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


