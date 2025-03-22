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

def canMakePalindromeQueries(self, s, queries):
    """
    :type s: str
    :type queries: List[List[int]]
    :rtype: List[bool]
    """
    def check(left1, right1, left2, right2):
        def same(left, right):
            return all(prefixs1[right+1][i]-prefixs1[left][i] == prefixs2[right+1][i]-prefixs2[left][i] for i in xrange(26))

        min_left, max_left = min(left1, left2), max(left1, left2)
        min_right, max_right = min(right1, right2), max(right1, right2)
        if not (prefix[min_left]-prefix[0] == prefix[-1]-prefix[max_right+1] == 0):
            return False
        if min_right < max_left:  # non-overlapped
            return prefix[max_left]-prefix[min_right+1] == 0 and same(min_left, min_right) and same(max_left, max_right)
        # overlapped
        if (left1 == min_left) == (right1 == max_right):  # inside another
            return same(min_left, max_right)
        # not inside another
        p1, p2 = (prefixs1, prefixs2) if min_left == left1 else (prefixs2, prefixs1)
        diff1 = [(p1[min_right+1][i]-p1[min_left][i])-(p2[max_left][i]-p2[min_left][i]) for i in xrange(26)]
        diff2 = [(p2[max_right+1][i]-p2[max_left][i])-(p1[max_right+1][i]-p1[min_right+1][i]) for i in xrange(26)]
        return diff1 == diff2 and all(x >= 0 for x in diff1)  # test case: s = "aabbba", queries = [[0,1,3,4]]

    prefix = [0]*(len(s)//2+1)
    prefixs1 = [[0]*26 for _ in xrange(len(s)//2+1)]
    prefixs2 = [[0]*26 for _ in xrange(len(s)//2+1)]
    for i in xrange(len(s)//2):
        x, y = ord(s[i])-ord('a'), ord(s[~i])-ord('a')
        prefix[i+1] = prefix[i]+int(x != y)
        for j in xrange(26):
            prefixs1[i+1][j] = prefixs1[i][j]+int(j == x)
            prefixs2[i+1][j] = prefixs2[i][j]+int(j == y)
    return [check(q[0], q[1], (len(s)-1)-q[3], (len(s)-1)-q[2]) for q in queries]


