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

def strongPasswordChecker(self, s):
    """
    :type s: str
    :rtype: int
    """
    missing_type_cnt = 3
    if any('a' <= c <= 'z' for c in s):
        missing_type_cnt -= 1
    if any('A' <= c <= 'Z' for c in s):
        missing_type_cnt -= 1
    if any(c.isdigit() for c in s):
        missing_type_cnt -= 1

    total_change_cnt = 0
    one_change_cnt, two_change_cnt, three_change_cnt = 0, 0, 0
    i = 2
    while i < len(s):
        if s[i] == s[i-1] == s[i-2]:
            length = 2
            while i < len(s) and s[i] == s[i-1]:
                length += 1
                i += 1

            total_change_cnt += length / 3
            if length % 3 == 0:
                one_change_cnt += 1
            elif length % 3 == 1:
                two_change_cnt += 1
            else:
                three_change_cnt += 1
        else:
            i += 1

    if len(s) < 6:
        return max(missing_type_cnt, 6 - len(s))
    elif len(s) <= 20:
        return max(missing_type_cnt, total_change_cnt)
    else:
        delete_cnt = len(s) - 20

        total_change_cnt -= min(delete_cnt, one_change_cnt * 1) / 1
        total_change_cnt -= min(max(delete_cnt - one_change_cnt, 0), two_change_cnt * 2) / 2
        total_change_cnt -= min(max(delete_cnt - one_change_cnt - 2 * two_change_cnt, 0), three_change_cnt * 3) / 3

        return delete_cnt + max(missing_type_cnt, total_change_cnt)



