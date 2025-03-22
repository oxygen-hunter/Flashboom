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

def differByOne(self, dict):
    """
    :type dict: List[str]
    :rtype: bool
    """
    MOD, P = 10**9+7, 113

    hashes = [0]*len(dict)
    for i, word in enumerate(dict):
        for c in word:
            hashes[i] = (P*hashes[i] + (ord(c)-ord('a'))) % MOD

    base = 1
    for p in reversed(xrange(len(dict[0]))):        
        lookup = collections.defaultdict(list)
        for i, word in enumerate(dict):
            new_hash = (hashes[i] - base*(ord(word[p])-ord('a'))) % MOD
            if new_hash in lookup:
                for j in lookup[new_hash]:
                    if dict[j][:p]+dict[j][p+1:] == word[:p]+word[p+1:]:
                        return True
            lookup[new_hash].append(i)
        base = P*base % MOD
    return False


