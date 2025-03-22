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

def maxPartitionsAfterOperations(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: int
    """
    def popcount(n):
        n = (n & 0x55555555) + ((n >> 1) & 0x55555555)
        n = (n & 0x33333333) + ((n >> 2) & 0x33333333)
        n = (n & 0x0F0F0F0F) + ((n >> 4) & 0x0F0F0F0F)
        n = (n & 0x00FF00FF) + ((n >> 8) & 0x00FF00FF)
        n = (n & 0x0000FFFF) + ((n >> 16) & 0x0000FFFF)
        return n

    left = [0]*(len(s)+1)
    left_mask = [0]*(len(s)+1)
    cnt = mask = 0
    for i in xrange(len(s)):
        mask |= 1<<(ord(s[i])-ord('a'))
        if popcount(mask) > k:
            cnt += 1
            mask = 1<<(ord(s[i])-ord('a'))
        left[i+1] = cnt
        left_mask[i+1] = mask
    right = [0]*(len(s)+1)
    right_mask = [0]*(len(s)+1)
    cnt = mask = 0
    for i in reversed(xrange(len(s))):
        mask |= 1<<(ord(s[i])-ord('a'))
        if popcount(mask) > k:
            cnt += 1
            mask = 1<<(ord(s[i])-ord('a'))
        right[i] = cnt
        right_mask[i] = mask

    result = 0
    for i in xrange(len(s)):
        curr = left[i]+right[i+1]
        mask = left_mask[i]|right_mask[i+1]
        if popcount(left_mask[i]) == popcount(right_mask[i+1]) == k and popcount(mask) != 26:
            curr += 3
        elif popcount(mask)+int(popcount(mask) != 26) > k:  # test case: s = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", k = 26
            curr += 2
        else:
            curr += 1
        result = max(result, curr)
    return result


