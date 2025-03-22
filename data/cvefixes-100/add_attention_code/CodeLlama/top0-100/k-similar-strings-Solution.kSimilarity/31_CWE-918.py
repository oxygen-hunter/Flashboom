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

def kSimilarity(self, A, B):
    """
    :type A: str
    :type B: str
    :rtype: int
    """
    def neighbors(s, B):
        for i, c in enumerate(s):
            if c != B[i]:
                break
        t = list(s)
        for j in xrange(i+1, len(s)):
            if t[j] == B[i]:
                t[i], t[j] = t[j], t[i]
                yield "".join(t)
                t[j], t[i] = t[i], t[j]

    q = collections.deque([A])
    lookup = set()
    result = 0
    while q:
        for _ in xrange(len(q)):
            s = q.popleft()
            if s == B:
                return result
            for t in neighbors(s, B):
                if t not in lookup:
                    lookup.add(t)
                    q.append(t)
        result += 1



