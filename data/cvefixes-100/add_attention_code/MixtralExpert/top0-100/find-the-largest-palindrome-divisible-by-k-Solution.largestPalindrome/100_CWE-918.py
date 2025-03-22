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

def largestPalindrome(self, n, k):
    """
    :type n: int
    :type k: int
    :rtype: str
    """
    def inv(x, p):
        return pow(x, p-2, p)

    def f(l):
        p = 7
        result = ['9']*l
        if l:                
            curr = reduce(lambda accu, x: (accu*10+(ord(x)-ord('0')))%p, result, 0)
            # l%2 == 0: (curr+(i-9)*11*pow(10, l//2-1, p))%p = 0
            # l%2 == 1: (curr+(i-9)*pow(10, l//2, p))%p = 0
            i = 9-(curr*inv(11 if l%2 == 0 else 1, p)*inv(pow(10, l//2-int(l%2 == 0), p), p))%p
            if i <= 2:
                i += p
            result[l//2] = result[l//2-int(l%2 == 0)] = str(i)
        return "".join(result)

    if k in (1, 3, 9):
        return '9'*n
    if k in (2, 4, 8):
        k = min(k, 6)
        if n <= k:
            return '8'*n
        l = k//2
        return '8'*l+'9'*(n-k)+'8'*l
    if k == 5:
        if n <= 2:
            return '5'*n
        return '5'+'9'*(n-2)+'5'
    if k == 6:
        if n <= 2:
            return '6'*n
        if n%2:
            l = n//2-1
            return '8'+'9'*l+'8'+'9'*l+'8'
        l = n//2-2
        return '8'+'9'*l+"77"+'9'*l+'8'
    l, r = divmod(n, 12)
    return "999999"*l+f(r)+"999999"*l  # 999999%7 = 0


