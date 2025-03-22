def render_books_list(data, sort_param, book_id, page):
    order = get_sort_function(sort_param, data)
    if data == "rated":
        return render_rated_books(page, book_id, order=order)
    elif data == "discover":
        return render_discover_books(page, book_id)
    elif data == "unread":
        return render_read_books(page, False, order=order)
    elif data == "read":
        return render_read_books(page, True, order=order)
    elif data == "hot":
        return render_hot_books(page, order)
    elif data == "download":
        return render_downloaded_books(page, order, book_id)
    elif data == "author":
        return render_author_books(page, book_id, order)
    elif data == "publisher":
        return render_publisher_books(page, book_id, order)
    elif data == "series":
        return render_series_books(page, book_id, order)
    elif data == "ratings":
        return render_ratings_books(page, book_id, order)
    elif data == "formats":
        return render_formats_books(page, book_id, order)
    elif data == "category":
        return render_category_books(page, book_id, order)
    elif data == "language":
        return render_language_books(page, book_id, order)
    elif data == "archived":
        return render_archived_books(page, order)
    elif data == "search":
        term = (request.args.get('query') or '')
        offset = int(int(config.config_books_per_page) * (page - 1))
        return render_search_results(term, offset, order, config.config_books_per_page)
    elif data == "advsearch":
        term = json.loads(flask_session['query'])
        offset = int(int(config.config_books_per_page) * (page - 1))
        return render_adv_search_results(term, offset, order, config.config_books_per_page)
    else:
        website = data or "newest"
        entries, random, pagination = calibre_db.fill_indexpage(page, 0, db.Books, True, order[0],
        														False, 0,
                                                                db.books_series_link,
                                                                db.Books.id == db.books_series_link.c.book,
                                                                db.Series)
        return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                     title=_(u"Books"), page=website, order=order[1])

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



