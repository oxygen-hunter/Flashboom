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

def longestDupSubstring(self, S):
    """
    :type S: str
    :rtype: str
    """
    M = 10**9+7
    D = 26

    def check(S, L):
        p = pow(D, L, M)
        curr = reduce(lambda x, y: (D*x+ord(y)-ord('a')) % M, S[:L], 0)
        lookup = collections.defaultdict(list)
        lookup[curr].append(L-1)
        for i in xrange(L, len(S)):
            curr = ((D*curr) % M + ord(S[i])-ord('a') -
                    ((ord(S[i-L])-ord('a'))*p) % M) % M
            if curr in lookup:
                for j in lookup[curr]:  # check if string is the same when hash is the same
                    if S[j-L+1:j+1] == S[i-L+1:i+1]:
                        return i-L+1
            lookup[curr].append(i)
        return 0

    left, right = 1, len(S)-1
    while left <= right:
        mid = left + (right-left)//2
        if not check(S, mid):
            right = mid-1
        else:
            left = mid+1
    result = check(S, right)
    return S[result:result + right]


