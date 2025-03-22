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

def maximumGain(self, s, x, y):
    """
    :type s: str
    :type x: int
    :type y: int
    :rtype: int
    """
    def score(s, a, x):
        i = result = 0
        for j in xrange(len(s)):
            s[i] = s[j]
            i += 1
            if i >= 2 and s[i-2:i] == a:
                i -= 2
                result += x
        s[:] = s[:i]
        return result
            
    s, a, b = list(s), list("ab"), list("ba")
    if x < y:
        x, y = y, x
        a, b = b, a
    return score(s, a, x) + score(s, b, y)


