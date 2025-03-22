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

def squareFreeSubsets(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    def linear_sieve_of_eratosthenes(n):  # Time: O(n), Space: O(n)
        primes = []
        spf = [-1]*(n+1)  # the smallest prime factor
        for i in xrange(2, n+1):
            if spf[i] == -1:
                spf[i] = i
                primes.append(i)
            for p in primes:
                if i*p > n or p > spf[i]:
                    break
                spf[i*p] = p
        return primes

    MAX_NUM = max(nums)
    PRIMES = linear_sieve_of_eratosthenes(MAX_NUM)
    MASKS = [0]*(MAX_NUM+1)
    for x in xrange(MAX_NUM+1):
        y = x
        for i, p in enumerate(PRIMES):
            if y%p:
                continue
            if y%p**2 == 0:
                MASKS[x] = 0
                break
            MASKS[x] |= (1<<i)
            y //= p
    MOD = 10**9+7

    cnt = collections.Counter(nums)
    arr = [x for x in cnt.iterkeys() if x != 1]
    dp = [[-1]*(1<<len(PRIMES)) for i in xrange(len(arr))]
    def memoization(i, mask):
        if i == len(arr):
            return 1
        if dp[i][mask] == -1:
            dp[i][mask] = memoization(i+1, mask)
            if MASKS[arr[i]] and (MASKS[arr[i]]&mask) == MASKS[arr[i]]:
                dp[i][mask] = (dp[i][mask]+cnt[arr[i]]*memoization(i+1, mask^MASKS[arr[i]]))%MOD
        return dp[i][mask]

    return (memoization(0, (1<<len(PRIMES))-1)*pow(2, cnt[1], MOD)-1)%MOD if 1 in cnt else (memoization(0, (1<<len(PRIMES))-1)-1)%MOD


