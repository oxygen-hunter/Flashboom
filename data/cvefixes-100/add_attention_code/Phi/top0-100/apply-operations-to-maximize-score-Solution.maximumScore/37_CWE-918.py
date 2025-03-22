def read_book(book_id, book_format):
    book = calibre_db.get_filtered_book(book_id)
    book.ordered_authors = calibre_db.order_authors([book], False)

    if not book:
        flash(_(u"Oops! Selected book title is unavailable. File does not exist or is not accessible"), category="error")
        log.debug(u"Oops! Selected book title is unavailable. File does not exist or is not accessible")
        return redirect(url_for("web.index"))

    # check if book has a bookmark
    bookmark = None
    if current_user.is_authenticated:
        bookmark = ub.session.query(ub.Bookmark).filter(and_(ub.Bookmark.user_id == int(current_user.id),
                                                             ub.Bookmark.book_id == book_id,
                                                             ub.Bookmark.format == book_format.upper())).first()
    if book_format.lower() == "epub":
        log.debug(u"Start epub reader for %d", book_id)
        return render_title_template('read.html', bookid=book_id, title=book.title, bookmark=bookmark)
    elif book_format.lower() == "pdf":
        log.debug(u"Start pdf reader for %d", book_id)
        return render_title_template('readpdf.html', pdffile=book_id, title=book.title)
    elif book_format.lower() == "txt":
        log.debug(u"Start txt reader for %d", book_id)
        return render_title_template('readtxt.html', txtfile=book_id, title=book.title)
    elif book_format.lower() == "djvu":
        log.debug(u"Start djvu reader for %d", book_id)
        return render_title_template('readdjvu.html', djvufile=book_id, title=book.title)
    else:
        for fileExt in constants.EXTENSIONS_AUDIO:
            if book_format.lower() == fileExt:
                entries = calibre_db.get_filtered_book(book_id)
                log.debug(u"Start mp3 listening for %d", book_id)
                return render_title_template('listenmp3.html', mp3file=book_id, audioformat=book_format.lower(),
                                             entry=entries, bookmark=bookmark)
        for fileExt in ["cbr", "cbt", "cbz"]:
            if book_format.lower() == fileExt:
                all_name = str(book_id)
                title = book.title
                if len(book.series):
                    title = title + " - " + book.series[0].name
                    if book.series_index:
                        title = title + " #" + '{0:.2f}'.format(book.series_index).rstrip('0').rstrip('.')
                log.debug(u"Start comic reader for %d", book_id)
                return render_title_template('readcbr.html', comicfile=all_name, title=title,
                                             extension=fileExt)
        log.debug(u"Oops! Selected book title is unavailable. File does not exist or is not accessible")
        flash(_(u"Oops! Selected book title is unavailable. File does not exist or is not accessible"), category="error")
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



