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

def minimumSwap(self, s1, s2):
    """
    :type s1: str
    :type s2: str
    :rtype: int
    """
    x1, y1 = 0, 0
    for i in xrange(len(s1)):
        if s1[i] == s2[i]:
            continue
        x1 += int(s1[i] == 'x')
        y1 += int(s1[i] == 'y')
    if x1%2 !=  y1%2:  # impossible
        return -1
    # case1: per xx or yy needs one swap, (x1//2 + y1//2) 
    # case2: per xy or yx needs two swaps, (x1%2 + y1%2)
    return (x1//2 + y1//2) + (x1%2 + y1%2)


