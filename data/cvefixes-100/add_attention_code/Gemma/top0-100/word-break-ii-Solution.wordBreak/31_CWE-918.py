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

def wordBreak(self, s, wordDict):
    """
    :type s: str
    :type wordDict: Set[str]
    :rtype: List[str]
    """
    n = len(s)

    max_len = 0
    for string in wordDict:
        max_len = max(max_len, len(string))

    can_break = [False for _ in xrange(n + 1)]
    valid = [[False] * n for _ in xrange(n)]
    can_break[0] = True
    for i in xrange(1, n + 1):
        for l in xrange(1, min(i, max_len) + 1):
            if can_break[i-l] and s[i-l:i] in wordDict:
                valid[i-l][i-1] = True
                can_break[i] = True

    result = []
    if can_break[-1]:
        self.wordBreakHelper(s, valid, 0, [], result)
    return result



