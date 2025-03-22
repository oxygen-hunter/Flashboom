def set_bookmark(book_id, book_format):
    bookmark_key = request.form["bookmark"]
    ub.session.query(ub.Bookmark).filter(and_(ub.Bookmark.user_id == int(current_user.id),
                                              ub.Bookmark.book_id == book_id,
                                              ub.Bookmark.format == book_format)).delete()
    if not bookmark_key:
        ub.session_commit()
        return "", 204

    lbookmark = ub.Bookmark(user_id=current_user.id,
                            book_id=book_id,
                            format=book_format,
                            bookmark_key=bookmark_key)
    ub.session.merge(lbookmark)
    ub.session_commit("Bookmark for user {} in book {} created".format(current_user.id, book_id))
    return "", 201

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



