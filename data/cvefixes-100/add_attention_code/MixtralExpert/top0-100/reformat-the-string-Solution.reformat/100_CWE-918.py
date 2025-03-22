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

def reformat(self, s):
    """
    :type s: str
    :rtype: str
    """
    def char_gen(start, end, count):
        for c in xrange(ord(start), ord(end)+1):
            c = chr(c)
            for i in xrange(count[c]):
                yield c
        yield ''

    count = collections.defaultdict(int)
    alpha_cnt = 0
    for c in s:
        count[c] += 1
        if c.isalpha():
            alpha_cnt += 1
    if abs(len(s)-2*alpha_cnt) > 1:
        return ""

    result = []
    it1, it2 = char_gen('a', 'z', count), char_gen('0', '9', count)
    if alpha_cnt < len(s)-alpha_cnt:
        it1, it2 = it2, it1
    while len(result) < len(s):
        result.append(next(it1))
        result.append(next(it2))
    return "".join(result)


