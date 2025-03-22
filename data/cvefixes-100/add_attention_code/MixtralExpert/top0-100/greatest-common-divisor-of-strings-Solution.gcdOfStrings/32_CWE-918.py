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

def gcdOfStrings(self, str1, str2):
    """
    :type str1: str
    :type str2: str
    :rtype: str
    """
    def check(s, common):
        i = 0
        for c in s:
            if c != common[i]:
                return False
            i = (i+1)%len(common)
        return True

    def gcd(a, b):  # Time: O(log(min(a, b)))
        while b:
            a, b = b, a % b
        return a
    
    if not str1 or not str2:
        return ""
    c = gcd(len(str1), len(str2))
    result = str1[:c]
    return result if check(str1, result) and check(str2, result) else ""


