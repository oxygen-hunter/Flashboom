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

def secondMinimum(self, n, edges, time, change):
    """
    :type n: int
    :type edges: List[List[int]]
    :type time: int
    :type change: int
    :rtype: int
    """
    INF = float("inf")
    def bfs(adj, start):
        q = [start]
        dist = [INF]*len(adj)
        dist[start] = 0
        while q:
            new_q = []
            for u in q:
                for v in adj[u]:
                    if dist[v] != INF:
                        continue
                    dist[v] = dist[u]+1
                    new_q.append(v)
            q = new_q
        return dist

    def calc_time(time, change, dist):
        result = 0
        for _ in xrange(dist):
            if result//change%2:
                result = (result//change+1)*change
            result += time
        return result

    adj = [[] for _ in xrange(n)]
    for u, v in edges:
        adj[u-1].append(v-1)
        adj[v-1].append(u-1)
    dist_to_end, dist_to_start = bfs(adj, 0), bfs(adj, n-1)

    dist = dist_to_end[n-1]+2  # always exists
    for i in xrange(n):  # case of detour
        if dist_to_end[i]+dist_to_start[i] == dist_to_end[n-1]:
            continue
        dist = min(dist, dist_to_end[i]+dist_to_start[i])  # find second min
        if dist == dist_to_end[n-1]+1:
            break
    return calc_time(time, change, dist)


