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

def betterCompression(self, compressed):
    """
    :type compressed: str
    :rtype: str
    """
    cnt = [0]*26
    x, curr = -1, 0
    for i in xrange(len(compressed)):
        if not compressed[i].isdigit():
            x = ord(compressed[i])-ord('a')
            continue
        curr = curr*10+int(compressed[i])
        if i+1 == len(compressed) or not compressed[i+1].isdigit():
            cnt[x] += curr
            curr = 0
    return "".join("%s%s" % (chr(ord('a')+i), x) for i, x in enumerate(cnt) if x)


