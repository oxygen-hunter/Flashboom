def read_book(book_id, book_format):
    book = calibre_db.get_filtered_book(book_id)
    book.ordered_authors = calibre_db.order_authors([book], False)

    if not book:
        flash(_(u"Oops! Selected book title is unavailable. File does not exist or is not accessible"), category="error")
        log.debug(u"Oops! Selected book title is unavailable. File does not exist or is not accessible")
        return redirect(url_for("web.index"))

    # check if book has a bookmark
    bookmark = None
    if current_user.is_authenticated:
        bookmark = ub.session.query(ub.Bookmark).filter(and_(ub.Bookmark.user_id == int(current_user.id),
                                                             ub.Bookmark.book_id == book_id,
                                                             ub.Bookmark.format == book_format.upper())).first()
    if book_format.lower() == "epub":
        log.debug(u"Start epub reader for %d", book_id)
        return render_title_template('read.html', bookid=book_id, title=book.title, bookmark=bookmark)
    elif book_format.lower() == "pdf":
        log.debug(u"Start pdf reader for %d", book_id)
        return render_title_template('readpdf.html', pdffile=book_id, title=book.title)
    elif book_format.lower() == "txt":
        log.debug(u"Start txt reader for %d", book_id)
        return render_title_template('readtxt.html', txtfile=book_id, title=book.title)
    elif book_format.lower() == "djvu":
        log.debug(u"Start djvu reader for %d", book_id)
        return render_title_template('readdjvu.html', djvufile=book_id, title=book.title)
    else:
        for fileExt in constants.EXTENSIONS_AUDIO:
            if book_format.lower() == fileExt:
                entries = calibre_db.get_filtered_book(book_id)
                log.debug(u"Start mp3 listening for %d", book_id)
                return render_title_template('listenmp3.html', mp3file=book_id, audioformat=book_format.lower(),
                                             entry=entries, bookmark=bookmark)
        for fileExt in ["cbr", "cbt", "cbz"]:
            if book_format.lower() == fileExt:
                all_name = str(book_id)
                title = book.title
                if len(book.series):
                    title = title + " - " + book.series[0].name
                    if book.series_index:
                        title = title + " #" + '{0:.2f}'.format(book.series_index).rstrip('0').rstrip('.')
                log.debug(u"Start comic reader for %d", book_id)
                return render_title_template('readcbr.html', comicfile=all_name, title=title,
                                             extension=fileExt)
        log.debug(u"Oops! Selected book title is unavailable. File does not exist or is not accessible")
        flash(_(u"Oops! Selected book title is unavailable. File does not exist or is not accessible"), category="error")
        return redirect(url_for("web.index"))

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


