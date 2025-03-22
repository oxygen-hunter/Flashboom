def create_book_on_upload(modif_date, meta):
    title = meta.title
    authr = meta.author
    sort_authors, input_authors, db_author, renamed_authors = prepare_authors_on_upload(title, authr)

    title_dir = helper.get_valid_filename(title, chars=96)
    author_dir = helper.get_valid_filename(db_author.name, chars=96)

    # combine path and normalize path from windows systems
    path = os.path.join(author_dir, title_dir).replace('\\', '/')

    # Calibre adds books with utc as timezone
    db_book = db.Books(title, "", sort_authors, datetime.utcnow(), datetime(101, 1, 1),
                       '1', datetime.utcnow(), path, meta.cover, db_author, [], "")

    modif_date |= modify_database_object(input_authors, db_book.authors, db.Authors, calibre_db.session,
                                         'author')

    # Add series_index to book
    modif_date |= edit_book_series_index(meta.series_id, db_book)

    # add languages
    invalid=[]
    modif_date |= edit_book_languages(meta.languages, db_book, upload=True, invalid=invalid)
    if invalid:
        for l in invalid:
            flash(_(u"'%(langname)s' is not a valid language", langname=l), category="warning")

    # handle tags
    modif_date |= edit_book_tags(meta.tags, db_book)

    # handle publisher
    modif_date |= edit_book_publisher(meta.publisher, db_book)

    # handle series
    modif_date |= edit_book_series(meta.series, db_book)

    # Add file to book
    file_size = os.path.getsize(meta.file_path)
    db_data = db.Data(db_book, meta.extension.upper()[1:], file_size, title_dir)
    db_book.data.append(db_data)
    calibre_db.session.add(db_book)

    # flush content, get db_book.id available
    calibre_db.session.flush()
    return db_book, input_authors, title_dir, renamed_authors

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


