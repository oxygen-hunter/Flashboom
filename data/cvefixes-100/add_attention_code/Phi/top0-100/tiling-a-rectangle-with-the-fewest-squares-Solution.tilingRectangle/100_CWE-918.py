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

def tilingRectangle(self, n, m):
    """
    :type n: int
    :type m: int
    :rtype: int
    """
    def find_next(board):
        for i in xrange(len(board)):
            for j in xrange(len(board[0])):
                if not board[i][j]:
                    return i, j
        return -1, -1

    def find_max_length(board, i, j):
        max_length = 1
        while i+max_length-1 < len(board) and \
              j+max_length-1 < len(board[0]):
            for r in xrange(i, i+max_length-1):
                if board[r][j+max_length-1]:
                    return max_length-1
            for c in xrange(j, j+max_length):
                if board[i+max_length-1][c]:
                    return max_length-1
            max_length += 1
        return max_length-1

    def fill(board, i, j, length, val):
        for r in xrange(i, i+length):
            for c in xrange(j, j+length):
                board[r][c] = val

    def backtracking(board, count, result):
        if count >= result[0]:  # pruning
            return
        i, j = find_next(board)
        if (i, j) == (-1, -1):  # finished
            result[0] = min(result[0], count)
            return
        max_length = find_max_length(board, i, j)
        for k in reversed(xrange(1, max_length+1)):
            fill(board, i, j, k, 1)
            backtracking(board, count+1, result)
            fill(board, i, j, k, 0)

    if m > n:
        return self.tilingRectangle(m, n)
    board = [[0]*m for _ in xrange(n)]
    result = [float("inf")]
    backtracking(board, 0, result)
    return result[0]


