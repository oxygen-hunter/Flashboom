def download_list():
    if current_user.get_view_property('download', 'dir') == 'desc':
        order = ub.User.name.desc()
        order_no = 0
    else:
        order = ub.User.name.asc()
        order_no = 1
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD) and current_user.role_admin():
        entries = ub.session.query(ub.User, func.count(ub.Downloads.book_id).label('count'))\
            .join(ub.Downloads).group_by(ub.Downloads.user_id).order_by(order).all()
        charlist = ub.session.query(func.upper(func.substr(ub.User.name, 1, 1)).label('char')) \
            .filter(ub.User.role.op('&')(constants.ROLE_ANONYMOUS) != constants.ROLE_ANONYMOUS) \
            .group_by(func.upper(func.substr(ub.User.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Downloads"), page="downloadlist", data="download", order=order_no)
    else:
        abort(404)

def maximumScore(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    MOD = 10**9+7
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
        return primes  # len(primes) = O(n/(logn-1)), reference: https://math.stackexchange.com/questions/264544/how-to-find-number-of-prime-numbers-up-to-to-n


    lookup = {}
    def count_of_distinct_prime_factors(x):
        y = x
        if y not in lookup:
            cnt = 0
            for p in primes:
                if p*p > x:
                    break
                if x%p != 0:
                    continue
                cnt += 1
                while x%p == 0:
                    x //= p
            if x != 1:
                cnt += 1
            lookup[y] = cnt
        return lookup[y]

    primes = linear_sieve_of_eratosthenes(int(max(nums)**0.5))
    scores = [count_of_distinct_prime_factors(x) for x in nums]

    left = [-1]*len(scores)
    stk = [-1]
    for i in xrange(len(scores)):
        while stk[-1] != -1 and scores[stk[-1]] < scores[i]:  # if multiple such elements exist, choose the one with the smallest index
            stk.pop()
        left[i] = stk[-1]
        stk.append(i)
    right = [-1]*len(scores)
    stk = [len(scores)]
    for i in reversed(xrange(len(scores))):
        while stk[-1] != len(scores) and scores[stk[-1]] <= scores[i]:
            stk.pop()
        right[i] = stk[-1]
        stk.append(i)
    
    result = 1
    max_heap = [(-x, i) for i, x in enumerate(nums)]
    heapq.heapify(max_heap)
    while max_heap:
        _, i = heapq.heappop(max_heap)
        c = min((i-left[i])*(right[i]-i), k)
        result = (result*pow(nums[i], c, MOD))%MOD
        k -= c
        if not k:
            break
    return result



