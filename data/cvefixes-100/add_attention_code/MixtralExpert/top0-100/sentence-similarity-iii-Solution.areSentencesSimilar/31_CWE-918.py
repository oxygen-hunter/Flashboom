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

def areSentencesSimilar(self, sentence1, sentence2):
    """
    :type sentence1: str
    :type sentence2: str
    :rtype: bool
    """
    if len(sentence1) > len(sentence2):
        sentence1, sentence2 = sentence2, sentence1
    count = 0
    for idx in (lambda x:x, lambda x:-1-x):
        for i in xrange(len(sentence1)+1):
            c1 = sentence1[idx(i)] if i != len(sentence1) else ' '
            c2 = sentence2[idx(i)] if i != len(sentence2) else ' '
            if c1 != c2:
                break
            if c1 == ' ':
                count += 1
    return count >= sentence1.count(' ')+1


