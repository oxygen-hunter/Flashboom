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

def deleteString(self, s):
    """
    :type s: str
    :rtype: int
    """
    MOD, P = 10**9+7, (113, 109)
    def hash(i, j):
        return [(prefix[idx][j+1]-prefix[idx][i]*power[idx][j-i+1])%MOD for idx in xrange(len(P))]

    if all(x == s[0] for x in s):
        return len(s)

    power = [[1] for _ in xrange(len(P))]
    prefix = [[0] for _ in xrange(len(P))]
    for x in s:
        for idx, p in enumerate(P):
            power[idx].append((power[idx][-1]*p)%MOD)
            prefix[idx].append((prefix[idx][-1]*p+(ord(x)-ord('a')))%MOD)
    dp = [1]*len(s)  # dp[i]: max operation count of s[i:]
    for i in reversed(xrange(len(s)-1)):
        for j in xrange(1, (len(s)-i)//2+1):
            if hash(i, i+j-1) == hash(i+j, i+2*j-1):
                dp[i] = max(dp[i], dp[i+j]+1)
    return dp[0]


