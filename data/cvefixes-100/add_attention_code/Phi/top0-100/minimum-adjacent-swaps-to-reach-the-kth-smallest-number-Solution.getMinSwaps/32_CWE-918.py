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

def getMinSwaps(self, num, k):
    """
    :type num: str
    :type k: int
    :rtype: int
    """
    def next_permutation(nums, begin, end):
        def reverse(nums, begin, end):
            left, right = begin, end-1
            while left < right:
                nums[left], nums[right] = nums[right], nums[left]
                left += 1
                right -= 1

        k, l = begin-1, begin
        for i in reversed(xrange(begin, end-1)):
            if nums[i] < nums[i+1]:
                k = i
                break
        else:
            reverse(nums, begin, end)
            return False
        for i in reversed(xrange(k+1, end)):
            if nums[i] > nums[k]:
                l = i
                break
        nums[k], nums[l] = nums[l], nums[k]
        reverse(nums, k+1, end)
        return True
    
    new_num = list(num)
    while k:
        next_permutation(new_num, 0, len(new_num))
        k -= 1
    result = 0
    for i in xrange(len(new_num)):
        if new_num[i] == num[i]:
            continue
        #   // greedily move the one with the least cost from new_num to num without missing optimal cost
        for j in xrange(i+1, len(new_num)):
            if new_num[j] == num[i]:
                break
        result += j-i
        for j in reversed(xrange(i+1, j+1)):
            new_num[j], new_num[j-1] = new_num[j-1], new_num[j]
    return result


