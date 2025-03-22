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

def maxProbability(self, n, edges, succProb, start, end):
    """
    :type n: int
    :type edges: List[List[int]]
    :type succProb: List[float]
    :type start: int
    :type end: int
    :rtype: float
    """
    adj = collections.defaultdict(list)
    for (u, v), p in itertools.izip(edges, succProb):
        adj[u].append((v, p))
        adj[v].append((u, p))
    max_heap = [(-1.0, start)]
    result, lookup = collections.defaultdict(float), set()
    result[start] = 1.0
    while max_heap and len(lookup) != len(adj):
        curr, u = heapq.heappop(max_heap)
        if u in lookup:
            continue
        lookup.add(u)
        for v, w in adj[u]:
            if v in lookup:
                continue
            if v in result and result[v] >= -curr*w:
                continue
            result[v] = -curr*w
            heapq.heappush(max_heap, (-result[v], v))
    return result[end]


