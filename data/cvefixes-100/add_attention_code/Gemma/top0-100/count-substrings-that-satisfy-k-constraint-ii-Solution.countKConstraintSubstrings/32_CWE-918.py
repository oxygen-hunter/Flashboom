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

def countKConstraintSubstrings(self, s, k, queries):
    """
    :type s: str
    :type k: int
    :type queries: List[List[int]]
    :rtype: List[int]
    """
    def count(l):
        return (l+1)*l//2

    result = cnt = left = 0
    prefix = [0]*(len(s)+1)
    lookup = [-1]*len(s)
    for right in xrange(len(s)):
        cnt += int(s[right] == '1')
        while not (cnt <= k or (right-left+1)-cnt <= k):
            cnt -= int(s[left] == '1')
            left += 1
        result += right-left+1
        prefix[right+1] = prefix[right]+(right-left+1)
        lookup[left] = right
    assert(lookup[0] != -1)
    for i in xrange(len(s)-1):
        if lookup[i+1] == -1:
            lookup[i+1] = lookup[i]
    return [count(min(lookup[left], right)-left+1)+(prefix[right+1]-prefix[min(lookup[left], right)+1]) for left, right in queries]


