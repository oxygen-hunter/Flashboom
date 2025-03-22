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

def maxGcdSum(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    def gcd(a, b):
        while b:
            a, b = b, a%b
        return a

    def binary_search_right(left, right, check):
        while left <= right:
            mid = left + (right-left)//2
            if not check(mid):
                right = mid-1
            else:
                left = mid+1
        return right

    # RMQ - Sparse Table
    # Template: https://github.com/kamyu104/GoogleCodeJam-Farewell-Rounds/blob/main/Round%20D/genetic_sequences2.py3
    # Time:  ctor:  O(NlogN) * O(fn)
    #        query: O(fn)
    # Space: O(NlogN)
    class SparseTable(object):
        def __init__(self, arr, fn):
            self.fn = fn
            self.bit_length = [0]
            n = len(arr)
            k = n.bit_length()-1  # log2_floor(n)
            for i in xrange(k+1):
                self.bit_length.extend(i+1 for _ in xrange(min(1<<i, (n+1)-len(self.bit_length))))
            self.st = [[0]*n for _ in xrange(k+1)]
            self.st[0] = arr[:]
            for i in xrange(1, k+1):  # Time: O(NlogN) * O(fn)
                for j in xrange((n-(1<<i))+1):
                    self.st[i][j] = fn(self.st[i-1][j], self.st[i-1][j+(1<<(i-1))])
    
        def query(self, L, R):  # Time: O(fn)
            i = self.bit_length[R-L+1]-1  # log2_floor(R-L+1)
            return self.fn(self.st[i][L], self.st[i][R-(1<<i)+1])
    
    prefix = [0]*(len(nums)+1)
    for i, x in enumerate(nums):
        prefix[i+1] = prefix[i]+x
    result = 0
    rmq = SparseTable(nums, gcd)
    for left, x in enumerate(nums):
        right = left
        while right < len(nums):  # O(logr) times
            g = rmq.query(left, right)
            right = binary_search_right(right, len(nums)-1, lambda x: rmq.query(left, x) >= g)  # Time: O(logn) * O(logr)
            if right-left+1 >= k:
                result = max(result, (prefix[right+1]-prefix[left])*g)
            right += 1
    return result


