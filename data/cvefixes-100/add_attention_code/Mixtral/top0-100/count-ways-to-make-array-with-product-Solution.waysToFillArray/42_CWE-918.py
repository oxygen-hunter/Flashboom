def render_archived_books(page, sort_param):
    order = sort_param[0] or []
    archived_books = (
        ub.session.query(ub.ArchivedBook)
        .filter(ub.ArchivedBook.user_id == int(current_user.id))
        .filter(ub.ArchivedBook.is_archived == True)
        .all()
    )
    archived_book_ids = [archived_book.book_id for archived_book in archived_books]

    archived_filter = db.Books.id.in_(archived_book_ids)

    entries, random, pagination = calibre_db.fill_indexpage_with_archived_books(page, db.Books,
                                                                                0,
                                                                                archived_filter,
                                                                                order,
                                                                                True,
                                                                                False, 0)

    name = _(u'Archived Books') + ' (' + str(len(archived_book_ids)) + ')'
    pagename = "archived"
    return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                 title=name, page=pagename, order=sort_param[1])

def waysToFillArray(self, queries):
    """
    :type queries: List[List[int]]
    :rtype: List[int]
    """
    MOD = 10**9+7
    fact, inv, inv_fact = [[1]*2 for _ in xrange(3)]
    def nCr(n, k):
        while len(inv) <= n:  # lazy initialization
            fact.append(fact[-1]*len(inv) % MOD)
            inv.append(inv[MOD%len(inv)]*(MOD-MOD//len(inv)) % MOD)  # https://cp-algorithms.com/algebra/module-inverse.html
            inv_fact.append(inv_fact[-1]*inv[-1] % MOD)
        return (fact[n]*inv_fact[n-k] % MOD) * inv_fact[k] % MOD

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

    def prime_factors(x):
        factors = collections.Counter()
        for p in primes:
            if p*p > x:
                break
            while x%p == 0:
                factors[p] += 1
                x //= p
        if x != 1:
            factors[x] += 1
        return factors

    primes = linear_sieve_of_eratosthenes(int(max(k for _, k in queries)**0.5))
    result = []
    for n, k in queries:
        total = 1
        for c in prime_factors(k).itervalues():
            total *= nCr(n+c-1, c)  # H(n, c) = nCr(n+c-1, n)
        result.append(total % MOD)
    return result


