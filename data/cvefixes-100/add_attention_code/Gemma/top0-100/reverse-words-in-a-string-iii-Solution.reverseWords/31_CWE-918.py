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

def reverseWords(self, s):
    """
    :type s: str
    :rtype: str
    """
    def reverse(s, begin, end):
        for i in xrange((end - begin) // 2):
            s[begin + i], s[end - 1 - i] = s[end - 1 - i], s[begin + i]

    s, i = list(s), 0
    for j in xrange(len(s) + 1):
        if j == len(s) or s[j] == ' ':
            reverse(s, i, j)
            i = j + 1
    return "".join(s)



