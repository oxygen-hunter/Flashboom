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

def maxSideLength(self, mat, threshold):
    """
    :type mat: List[List[int]]
    :type threshold: int
    :rtype: int
    """
    def check(dp, mid, threshold):
        for i in xrange(mid, len(dp)):
            for j in xrange(mid, len(dp[0])):
                if dp[i][j] - dp[i-mid][j] - dp[i][j-mid] + dp[i-mid][j-mid] <= threshold:
                    return True
        return False
    
    dp = [[0 for _ in xrange(len(mat[0])+1)] for _ in xrange(len(mat)+1)]
    for i in xrange(1, len(mat)+1):
        for j in xrange(1, len(mat[0])+1):
            dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + mat[i-1][j-1]

    left, right = 0, min(len(mat), len(mat[0])+1)
    while left <= right:
        mid = left + (right-left)//2
        if not check(dp, mid, threshold):
            right = mid-1
        else:
            left = mid+1
    return right


