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

def subsetXORSum(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    # given there are k (k >= 1) nums of which ith bit is 1,
    # the bit contributes to sum is:
    # (nCr(k, 1) + nCr(k, 3) + ...) * (nCr(n - k, 0) + nCr(n - k, 1) + ...) * 2^i
    # = 2^(k-1) * 2^(n-k) = 2^(n-1) * 2^i
    result = 0
    for x in nums:
        result |= x
    return result * 2**(len(nums)-1)


