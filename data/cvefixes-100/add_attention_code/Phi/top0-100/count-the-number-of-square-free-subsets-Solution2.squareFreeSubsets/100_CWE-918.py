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


