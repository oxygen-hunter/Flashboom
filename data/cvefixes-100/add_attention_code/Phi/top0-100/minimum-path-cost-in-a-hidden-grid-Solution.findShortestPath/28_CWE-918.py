def login():
    if current_user is not None and current_user.is_authenticated:
        return redirect(url_for('web.index'))
    if config.config_login_type == constants.LOGIN_LDAP and not services.ldap:
        log.error(u"Cannot activate LDAP authentication")
        flash(_(u"Cannot activate LDAP authentication"), category="error")
    if request.method == "POST":
        form = request.form.to_dict()
        user = ub.session.query(ub.User).filter(func.lower(ub.User.name) == form['username'].strip().lower()) \
            .first()
        if config.config_login_type == constants.LOGIN_LDAP and services.ldap and user and form['password'] != "":
            login_result, error = services.ldap.bind_user(form['username'], form['password'])
            if login_result:
                login_user(user, remember=bool(form.get('remember_me')))
                ub.store_user_session()
                log.debug(u"You are now logged in as: '%s'", user.name)
                flash(_(u"you are now logged in as: '%(nickname)s'", nickname=user.name),
                      category="success")
                return redirect_back(url_for("web.index"))
            elif login_result is None and user and check_password_hash(str(user.password), form['password']) \
                and user.name != "Guest":
                login_user(user, remember=bool(form.get('remember_me')))
                ub.store_user_session()
                log.info("Local Fallback Login as: '%s'", user.name)
                flash(_(u"Fallback Login as: '%(nickname)s', LDAP Server not reachable, or user not known",
                        nickname=user.name),
                      category="warning")
                return redirect_back(url_for("web.index"))
            elif login_result is None:
                log.info(error)
                flash(_(u"Could not login: %(message)s", message=error), category="error")
            else:
                ip_Address = request.headers.get('X-Forwarded-For', request.remote_addr)
                log.warning('LDAP Login failed for user "%s" IP-address: %s', form['username'], ip_Address)
                flash(_(u"Wrong Username or Password"), category="error")
        else:
            ip_Address = request.headers.get('X-Forwarded-For', request.remote_addr)
            if 'forgot' in form and form['forgot'] == 'forgot':
                if user is not None and user.name != "Guest":
                    ret, __ = reset_password(user.id)
                    if ret == 1:
                        flash(_(u"New Password was send to your email address"), category="info")
                        log.info('Password reset for user "%s" IP-address: %s', form['username'], ip_Address)
                    else:
                        log.error(u"An unknown error occurred. Please try again later")
                        flash(_(u"An unknown error occurred. Please try again later."), category="error")
                else:
                    flash(_(u"Please enter valid username to reset password"), category="error")
                    log.warning('Username missing for password reset IP-address: %s', ip_Address)
            else:
                if user and check_password_hash(str(user.password), form['password']) and user.name != "Guest":
                    login_user(user, remember=bool(form.get('remember_me')))
                    ub.store_user_session()
                    log.debug(u"You are now logged in as: '%s'", user.name)
                    flash(_(u"You are now logged in as: '%(nickname)s'", nickname=user.name), category="success")
                    config.config_is_initial = False
                    return redirect_back(url_for("web.index"))
                else:
                    log.warning('Login failed for user "%s" IP-address: %s', form['username'], ip_Address)
                    flash(_(u"Wrong Username or Password"), category="error")

    next_url = request.args.get('next', default=url_for("web.index"), type=str)
    if url_for("web.logout") == next_url:
        next_url = url_for("web.index")
    return render_title_template('login.html',
                                 title=_(u"Login"),
                                 next_url=next_url,
                                 config=config,
                                 oauth_check=oauth_check,
                                 mail=config.get_mail_server_configured(), page="login")

def findShortestPath(self, master):
    """
    :type master: GridMaster
    :rtype: int
    """
    directions = {'L': (0, -1), 'R': (0, 1), 'U': (-1, 0), 'D': (1, 0)}
    rollback = {'L': 'R', 'R': 'L', 'U': 'D', 'D': 'U'}

    def dfs(pos, target, master, lookup, adj):
        if target[0] is None and master.isTarget():
            target[0] = pos
        lookup.add(pos)
        for d, (di, dj) in directions.iteritems():
            if not master.canMove(d):
                continue
            nei = (pos[0]+di, pos[1]+dj)
            if nei in adj[pos]:
                continue
            adj[pos][nei] = master.move(d)
            if nei not in lookup:
                dfs(nei, target, master, lookup, adj)
            adj[nei][pos] = master.move(rollback[d])
                    
    def dijkstra(adj, start, target):
        dist = {start:0}
        min_heap = [(0, start)]
        while min_heap:
            curr, u = heapq.heappop(min_heap)
            if dist[u] < curr:
                continue
            for v, w in adj[u].iteritems():
                if v in dist and dist[v] <= curr+w:
                    continue
                dist[v] = curr+w
                heapq.heappush(min_heap, (curr+w, v))
        return dist[target] if target in dist else -1 
    
    start = (0, 0)
    target = [None]
    adj = collections.defaultdict(dict)
    dfs(start, target, master, set(), adj)
    if not target[0]:
        return -1
    return dijkstra(adj, start, target[0])


