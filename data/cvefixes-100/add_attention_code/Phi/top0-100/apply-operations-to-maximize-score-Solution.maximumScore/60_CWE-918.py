def show_book(book_id):
    entries = calibre_db.get_book_read_archived(book_id, config.config_read_column, allow_show_archived=True)
    if entries:
        read_book = entries[1]
        archived_book = entries[2]
        entry = entries[0]
        entry.read_status = read_book == ub.ReadBook.STATUS_FINISHED
        entry.is_archived = archived_book
        for index in range(0, len(entry.languages)):
            entry.languages[index].language_name = isoLanguages.get_language_name(get_locale(), entry.languages[
                index].lang_code)
        cc = get_cc_columns(filter_config_custom_read=True)
        book_in_shelfs = []
        shelfs = ub.session.query(ub.BookShelf).filter(ub.BookShelf.book_id == book_id).all()
        for sh in shelfs:
            book_in_shelfs.append(sh.shelf)

        entry.tags = sort(entry.tags, key=lambda tag: tag.name)

        entry.ordered_authors = calibre_db.order_authors([entry])

        entry.kindle_list = check_send_to_kindle(entry)
        entry.reader_list = check_read_formats(entry)

        entry.audioentries = []
        for media_format in entry.data:
            if media_format.format.lower() in constants.EXTENSIONS_AUDIO:
                entry.audioentries.append(media_format.format.lower())

        return render_title_template('detail.html',
                                     entry=entry,
                                     cc=cc,
                                     is_xhr=request.headers.get('X-Requested-With')=='XMLHttpRequest',
                                     title=entry.title,
                                     books_shelfs=book_in_shelfs,
                                     page="book")
    else:
        log.debug(u"Oops! Selected book title is unavailable. File does not exist or is not accessible")
        flash(_(u"Oops! Selected book title is unavailable. File does not exist or is not accessible"),
              category="error")
        return redirect(url_for("web.index"))

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



