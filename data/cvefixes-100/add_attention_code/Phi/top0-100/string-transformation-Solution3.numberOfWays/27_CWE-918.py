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

def numberOfWays(self, s, t, k):
    """
    :type s: str
    :type t: str
    :type k: int
    :rtype: int
    """
    MOD = 10**9+7
    def matrix_mult(A, B):
        ZB = zip(*B)
        return [[sum(a*b % MOD for a, b in itertools.izip(row, col)) % MOD for col in ZB] for row in A]
 
    def matrix_expo(A, K):
        result = [[int(i == j) for j in xrange(len(A))] for i in xrange(len(A))]
        while K:
            if K % 2:
                result = matrix_mult(result, A)
            A = matrix_mult(A, A)
            K /= 2
        return result

    # Template: https://cp-algorithms.com/string/z-function.html
    def z_function(s):  # Time: O(n), Space: O(n)
        z = [0]*len(s)
        l, r = 0, 0
        for i in xrange(1, len(z)):
            if i <= r:
                z[i] = min(r-i+1, z[i-l])
            while i+z[i] < len(z) and s[z[i]] == s[i+z[i]]:
                z[i] += 1
            if i+z[i]-1 > r:
                l, r = i, i+z[i]-1
        return z

    n = len(s)
    T = [[0, 1],
         [n-1, (n-1)-1]]
    dp = [1, 0]
    dp = matrix_mult([dp], matrix_expo(T, k))[0]  # [dp[0], dp[1]] * T^k
    z = z_function(t+s+s[:-1])
    return reduce(lambda a, b: (a+b)%MOD, (dp[int(i != 0)] for i in xrange(n) if z[i+len(t)] >= len(t)), 0)


