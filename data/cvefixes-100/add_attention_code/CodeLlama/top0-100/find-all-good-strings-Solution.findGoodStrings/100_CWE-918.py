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

def findGoodStrings(self, n, s1, s2, evil):
    """
    :type n: int
    :type s1: str
    :type s2: str
    :type evil: str
    :rtype: int
    """
    MOD = 10**9+7
    def getPrefix(pattern):
        prefix = [-1]*len(pattern)
        j = -1
        for i in xrange(1, len(pattern)):
            while j != -1 and pattern[j+1] != pattern[i]:
                j = prefix[j]
            if pattern[j+1] == pattern[i]:
                j += 1
            prefix[i] = j
        return prefix

    prefix = getPrefix(evil)
    dp = [[[[0]*len(evil) for _ in xrange(2)] for _ in xrange(2)] for _ in xrange(2)]
    dp[0][0][0][0] = 1
    for i in xrange(n):
        dp[(i+1)%2] = [[[0]*len(evil) for _ in xrange(2)] for _ in xrange(2)]
        for j in xrange(2):
            for k in xrange(2):
                min_c = 'a' if j else s1[i]
                max_c = 'z' if k else s2[i]
                for l in xrange(len(evil)):
                    if not dp[i%2][j][k][l]:
                        continue
                    for c in xrange(ord(min_c)-ord('a'), ord(max_c)-ord('a')+1):
                        c = chr(c+ord('a'))
                        m = l-1
                        while m != -1 and evil[m+1] != c:
                            m = prefix[m]
                        if evil[m+1] == c:
                            m += 1
                        if m+1 == len(evil):
                            continue
                        dp[(i+1)%2][j or (s1[i] != c)][k or (s2[i] != c)][m+1] = \
                            (dp[(i+1)%2][j or (s1[i] != c)][k or (s2[i] != c)][m+1] + dp[i%2][j][k][l]) % MOD
    result = 0
    for j in xrange(2):
        for k in xrange(2):
            for l in xrange(len(evil)):
                result = (result + dp[n%2][j][k][l]) % MOD
    return result


