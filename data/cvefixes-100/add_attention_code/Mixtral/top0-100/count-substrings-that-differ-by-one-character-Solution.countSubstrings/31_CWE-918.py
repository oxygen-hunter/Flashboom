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

def countSubstrings(self, s, t):
    """
    :type s: str
    :type t: str
    :rtype: int
    """
    def count(i, j):  # for each possible alignment, count the number of substrs that differ by 1 char
        result = left_cnt = right_cnt = 0  # left and right consecutive same counts relative to the different char
        for k in xrange(min(len(s)-i, len(t)-j)):
            right_cnt += 1
            if s[i+k] != t[j+k]:
                left_cnt, right_cnt = right_cnt, 0
                # prev_i = i+k-prev+1
            result += left_cnt  # target substrs are [s[left_i+c:i+k+1] for c in xrange(left_cnt)]
        return result

    return sum(count(i, 0) for i in xrange(len(s))) + \
           sum(count(0, j) for j in xrange(1, len(t)))


