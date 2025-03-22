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

def numberOfGoodSubsets(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    def sieve_of_eratosthenes(n):  # Time: O(n * log(logn)), Space: O(n)
        if n < 2:
            return []
        primes = [2]
        is_prime = [True]*((n+1)//2)
        for i in xrange(1, len(is_prime)):
            if not is_prime[i]:
                continue
            primes.append(2*i+1)
            for j in xrange(2*i*(i+1), len(is_prime), (2*i+1)):
                is_prime[j] = False
        return primes

    def to_mask(primes, x):
        mask, basis = 0, 1
        for p in primes:
            if x%p == 0:
                mask |= basis
            basis <<= 1
        return mask

    MOD = 10**9+7
    primes = sieve_of_eratosthenes(max(nums))
    dp = [0]*(1<<len(primes))  # dp[i] = the number of different good subsets of which the total product equals to the product of the primes in bitset i
    dp[0] = 1
    cnts = collections.Counter(nums)
    for x, cnt in cnts.iteritems():
        if x == 1 or any(x%(p*p) == 0 for p in primes if p*p <= x):
            continue
        mask = to_mask(primes, x)
        for i in xrange(len(dp)-1):
            if i&mask:
                continue
            dp[i|mask] = (dp[i|mask]+cnt*dp[i])%MOD
    return (pow(2, cnts[1], MOD))*(reduce(lambda total, x: (total+x)%MOD, dp, 0)-1)%MOD


