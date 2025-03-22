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

def createSortedArray(self, instructions):
    """
    :type instructions: List[int]
    :rtype: int
    """
    MOD = 10**9 + 7
    def smallerMergeSort(idxs, start, end, counts):
        if end - start <= 0:  # The size of range [start, end] less than 2 is always with count 0.
            return 0

        mid = start + (end - start) // 2
        smallerMergeSort(idxs, start, mid, counts)
        smallerMergeSort(idxs, mid + 1, end, counts)
        r = start
        tmp = []
        for i in xrange(mid+1, end + 1):
            # Merge the two sorted arrays into tmp.
            while r <= mid and idxs[r][0] < idxs[i][0]:
                tmp.append(idxs[r])
                r += 1
            tmp.append(idxs[i])
            counts[idxs[i][1]] += r - start
        while r <= mid:
            tmp.append(idxs[r])
            r += 1
        # Copy tmp back to idxs
        idxs[start:start+len(tmp)] = tmp
    
    def largerMergeSort(idxs, start, end, counts):
        if end - start <= 0:  # The size of range [start, end] less than 2 is always with count 0.
            return 0

        mid = start + (end - start) // 2
        largerMergeSort(idxs, start, mid, counts)
        largerMergeSort(idxs, mid + 1, end, counts)
        r = start
        tmp = []
        for i in xrange(mid+1, end + 1):
            # Merge the two sorted arrays into tmp.
            while r <= mid and idxs[r][0] <= idxs[i][0]:
                tmp.append(idxs[r])
                r += 1
            if r <= mid:
                tmp.append(idxs[i])
            counts[idxs[i][1]] += mid - r + 1
        while r <= mid:
            tmp.append(idxs[r])
            r += 1
        # Copy tmp back to idxs
        idxs[start:start+len(tmp)] = tmp

    idxs = []
    smaller_counts, larger_counts = [[0] * len(instructions) for _ in xrange(2)]
    for i, inst in enumerate(instructions):
        idxs.append((inst, i))
    smallerMergeSort(idxs[:], 0, len(idxs)-1, smaller_counts)
    largerMergeSort(idxs, 0, len(idxs)-1, larger_counts)
    return sum(min(s, l) for s, l in itertools.izip(smaller_counts, larger_counts)) % MOD


