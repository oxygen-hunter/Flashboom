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

def minimumSize(self, nums, maxOperations):
    """
    :type nums: List[int]
    :type maxOperations: int
    :rtype: int
    """
    def check(nums, maxOperations, x):
        return sum((num+x-1)//x-1 for num in nums) <= maxOperations

    left, right = 1, max(nums)
    while left <= right:
        mid = left + (right-left)//2
        if check(nums, maxOperations, mid):
            right = mid-1
        else:
            left = mid+1
    return left


