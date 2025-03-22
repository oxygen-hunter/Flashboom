def change_profile(kobo_support, local_oauth_check, oauth_status, translations, languages):
    to_save = request.form.to_dict()
    current_user.random_books = 0
    if current_user.role_passwd() or current_user.role_admin():
        if to_save.get("password"):
            current_user.password = generate_password_hash(to_save["password"])
    try:
        if to_save.get("kindle_mail", current_user.kindle_mail) != current_user.kindle_mail:
            current_user.kindle_mail = valid_email(to_save["kindle_mail"])
        if to_save.get("email", current_user.email) != current_user.email:
            current_user.email = check_email(to_save["email"])
        if current_user.role_admin():
            if to_save.get("name", current_user.name) != current_user.name:
                # Query User name, if not existing, change
                current_user.name = check_username(to_save["name"])
        current_user.random_books = 1 if to_save.get("show_random") == "on" else 0
        if to_save.get("default_language"):
            current_user.default_language = to_save["default_language"]
        if to_save.get("locale"):
            current_user.locale = to_save["locale"]
        old_state = current_user.kobo_only_shelves_sync
        # 1 -> 0: nothing has to be done
        # 0 -> 1: all synced books have to be added to archived books, + currently synced shelfs which
        # don't have to be synced have to be removed (added to Shelf archive)
        current_user.kobo_only_shelves_sync = int(to_save.get("kobo_only_shelves_sync") == "on") or 0
        if old_state == 0 and current_user.kobo_only_shelves_sync == 1:
            kobo_sync_status.update_on_sync_shelfs(current_user.id)

    except Exception as ex:
        flash(str(ex), category="error")
        return render_title_template("user_edit.html",
                                     content=current_user,
                                     translations=translations,
                                     profile=1,
                                     languages=languages,
                                     title=_(u"%(name)s's profile", name=current_user.name),
                                     page="me",
                                     kobo_support=kobo_support,
                                     registered_oauth=local_oauth_check,
                                     oauth_status=oauth_status)

    val = 0
    for key, __ in to_save.items():
        if key.startswith('show'):
            val += int(key[5:])
    current_user.sidebar_view = val
    if to_save.get("Show_detail_random"):
        current_user.sidebar_view += constants.DETAIL_RANDOM

    try:
        ub.session.commit()
        flash(_(u"Profile updated"), category="success")
        log.debug(u"Profile updated")
    except IntegrityError:
        ub.session.rollback()
        flash(_(u"Found an existing account for this e-mail address"), category="error")
        log.debug(u"Found an existing account for this e-mail address")
    except OperationalError as e:
        ub.session.rollback()
        log.error("Database error: %s", e)
        flash(_(u"Database error: %(error)s.", error=e), category="error")

def modifiedGraphEdges(self, n, edges, source, destination, target):
    """
    :type n: int
    :type edges: List[List[int]]
    :type source: int
    :type destination: int
    :type target: int
    :rtype: List[List[int]]
    """
    def dijkstra(start, x):
        best = [target+1]*len(adj)
        best[start] = 0
        min_heap = [(0, start)]
        while min_heap:
            curr, u = heapq.heappop(min_heap)
            if curr > best[u]:
                continue
            for v, w in adj[u]:       
                if w == -1:
                    w = x
                if curr+w >= best[v]:
                    continue
                best[v] = curr+w
                heapq.heappush(min_heap, (best[v], v))
        return best
    
    adj = [[] for _ in xrange(n)]
    for u, v, w in edges:
        adj[u].append((v, w))
        adj[v].append((u, w))
    left = dijkstra(source, 1)
    if not (left[destination] <= target):
        return []
    right= dijkstra(destination, target+1)
    if not (right[source] >= target):
        return []
    for e in edges:
        if e[2] == -1:
            e[2] = max(target-left[e[0]]-right[e[1]], target-left[e[1]]-right[e[0]], 1)
    return edges


