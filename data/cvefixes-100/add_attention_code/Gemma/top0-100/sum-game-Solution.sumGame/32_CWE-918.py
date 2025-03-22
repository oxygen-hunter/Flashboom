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

def sumGame(self, num):
    """
    :type num: str
    :rtype: bool
    """
    # (1) if both halfs have '?',
    #     alice will optimally choose 9 or 0 from one half to maximize or minimize the diff of both half sums,
    #     and bob will optimally choose the same number from the other half to minimize or maximize the diff of both half sums.
    #     in the end, it turns that only one half has '?' and the diff of both half sums is still the same as original
    # (2) if smaller half has no '?', then alice wins
    # (3) if smaller half has '?'
    #     (3.1) if cnt of '?' is odd, alice can choose the last number to make the diff of both half sums != 0, then alice wins
    #     (3.2) if cnt of '?' is even
    #           (3.2.1) if larger-smaller = cnt/2 * 9, bob can always make a pair of sum 9 no matter what alice chooses, then bob wins
    #           (3.2.2) if larger-smaller > cnt/2 * 9, alice can always choose 0 no matter what bob chooses, then alice wins
    #           (3.2.3) if larger-smaller < cnt/2 * 9, alice can always choose 9 no matter what bob chooses, then alice wins
    cnt = total = 0
    for i in xrange(len(num)):
        if num[i] == '?':
            cnt += (-1 if i < len(num)//2 else 1)
        else:
            total += (int(num[i]) if i < len(num)//2 else -int(num[i]))
    return True if cnt%2 else total != cnt//2*9


