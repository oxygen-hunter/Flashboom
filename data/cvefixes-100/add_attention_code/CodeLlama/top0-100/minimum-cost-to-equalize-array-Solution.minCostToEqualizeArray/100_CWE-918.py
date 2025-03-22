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

def minCostToEqualizeArray(self, nums, cost1, cost2):
    """
    :type nums: List[int]
    :type cost1: int
    :type cost2: int
    :rtype: int
    """
    MOD = 10**9+7

    n = len(nums)
    mx = max(nums)
    total = mx*n-sum(nums)

    # fill until mx with only cost1 operations
    if n <= 2 or cost1*2 <= cost2:
        return total*cost1%MOD

    result = float("inf")
    # fill until mx with more cost2 operations and fewer cost1 operations
    mn = min(nums)
    cnt1 = max((mx-mn)-(total-(mx-mn)), 0)
    cnt2 = total-cnt1
    result = min(result, (cnt1+cnt2%2)*cost1 + cnt2//2*cost2)

    # fill until mx+x with most cost2 operations and fewest cost1 operations,
    # where x is the  max of x s.t. cnt1+x >= (n-1)*x => cnt1 >= (n-2)*x
    x, cnt1 = divmod(cnt1, (n-2))
    total += n*x
    cnt2 = total-cnt1
    result = min(result, (cnt1+cnt2%2)*cost1 + (cnt2//2)*cost2)

    # fill until mx+x+1 or mx+x+2 with nearly all cost2 operations and at most one cost1 operation
    for _ in xrange(2):  # increase twice is for odd n
        total += n
        result = min(result, total%2*cost1 + total//2*cost2)
    return result%MOD


