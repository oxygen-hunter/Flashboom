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

def collectTheCoins(self, coins, edges):
    """
    :type coins: List[int]
    :type edges: List[List[int]]
    :rtype: int
    """
    DISTANCE = 2

    adj = [set() for _ in xrange(len(coins))]
    for u, v in edges:
        adj[u].add(v)
        adj[v].add(u)
    n = len(coins)
    q = []
    for u in xrange(len(coins)):
        while len(adj[u]) == 1 and not coins[u]:
            v = adj[u].pop()
            adj[v].remove(u)
            n -= 1
            u = v
    q = [u for u in xrange(len(coins)) if len(adj[u]) == 1]
    for _ in xrange(DISTANCE):
        new_q = []
        for u in q:
            if not adj[u]:
                assert(n == 1)
                break
            v = adj[u].pop()
            adj[v].remove(u)
            n -= 1
            if len(adj[v]) == 1:
                new_q.append(v)
        q = new_q
    return (n-1)*2


