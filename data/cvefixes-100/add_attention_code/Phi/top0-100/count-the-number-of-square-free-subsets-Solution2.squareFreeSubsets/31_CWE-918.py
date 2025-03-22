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


