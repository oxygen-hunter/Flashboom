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

def numberOfPatterns(self, m, n):
    """
    :type m: int
    :type n: int
    :rtype: int
    """
    def merge(used, i):
        return used | (1 << i)

    def contain(used, i):
        return bool(used & (1 << i))

    def convert(i, j):
        return 3 * i + j

    def numberOfPatternsHelper(m, n, level, used, i):
        number = 0
        if level > n:
            return number

        if m <= level <= n:
            number += 1

        x1, y1 = divmod(i, 3)
        for j in xrange(9):
            if contain(used, j):
                continue

            x2, y2 = divmod(j, 3)
            if ((x1 == x2 and abs(y1 - y2) == 2) or
                (y1 == y2 and abs(x1 - x2) == 2) or
                (abs(x1 - x2) == 2 and abs(y1 - y2) == 2)) and \
               not contain(used,
                           convert((x1 + x2) // 2, (y1 + y2) // 2)):
                    continue

            number += numberOfPatternsHelper(m, n, level + 1, merge(used, j), j)

        return number

    number = 0
    # 1, 3, 7, 9
    number += 4 * numberOfPatternsHelper(m, n, 1, merge(0, 0), 0)
    # 2, 4, 6, 8
    number += 4 * numberOfPatternsHelper(m, n, 1, merge(0, 1), 1)
    # 5
    number += numberOfPatternsHelper(m, n, 1, merge(0, 4), 4)
    return number



