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

def maxHeight(self, cuboids):
    """
    :type cuboids: List[List[int]]
    :rtype: int
    """
    for cuboid in cuboids:
        cuboid.sort()
    cuboids.append([0, 0, 0])
    cuboids.sort()
    dp = [0]*len(cuboids)
    for i in xrange(1, len(cuboids)):
        for j in xrange(i):
            if all(cuboids[j][k] <= cuboids[i][k] for k in xrange(3)):
                dp[i] = max(dp[i], dp[j]+cuboids[i][2])
    return max(dp)


