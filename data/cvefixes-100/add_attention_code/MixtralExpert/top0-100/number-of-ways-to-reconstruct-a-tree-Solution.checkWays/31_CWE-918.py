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

def checkWays(self, pairs):
    """
    :type pairs: List[List[int]]
    :rtype: int
    """
    adj = collections.defaultdict(set)
    for x, y in pairs:
        adj[x].add(y)
        adj[y].add(x)
    n, mul = len(adj), False
    lookup = set()
    for node in sorted(adj.iterkeys(), key=lambda i: len(adj[i]), reverse=True):
        lookup.add(node)
        parent = 0
        for x in adj[node]:
            if x not in lookup:
                continue
            if parent == 0 or len(adj[x]) < len(adj[parent]):
                parent = x
        if parent:
            if any(True for x in adj[node] if x != parent and x not in adj[parent]):
                return 0
            mul |= len(adj[parent]) == len(adj[node])
        elif len(adj[node]) != n-1:
            return 0
    return 1 + mul


