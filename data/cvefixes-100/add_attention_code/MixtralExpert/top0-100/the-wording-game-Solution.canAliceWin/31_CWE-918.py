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

def canAliceWin(self, a, b):
    """
    :type a: List[str]
    :type b: List[str]
    :rtype: bool
    """
    def is_closely_greater(a, b):
        return ord(a[0])-ord(b[0]) <= 1 and a > b

    result = True
    i, j = 0, -1
    for _ in xrange(len({w[0] for w in a})+len({w[0] for w in b})):  # each player takes turns using a word with a different first letter than the last word he played
        j = next((j for j in xrange(j+1, len(b)) if is_closely_greater(b[j], a[i])), len(b))
        if j == len(b):
            break
        while j+1 < len(b) and b[j+1][0] == b[j][0]:  # play the lexicographically greatest word with the same first letter
            j += 1
        a, b, i, j, result = b, a, j, i, not result
    return result


