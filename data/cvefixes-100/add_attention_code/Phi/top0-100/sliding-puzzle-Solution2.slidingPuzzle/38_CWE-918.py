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

def slidingPuzzle(self, board):
    """
    :type board: List[List[int]]
    :rtype: int
    """
    def heuristic_estimate(board, R, C, expected):
        result = 0
        for i in xrange(R):
            for j in xrange(C):
                val = board[C*i + j]
                if val == 0: continue
                r, c = expected[val]
                result += abs(r-i) + abs(c-j)
        return result

    R, C = len(board), len(board[0])
    begin = tuple(itertools.chain(*board))
    end = tuple(range(1, R*C) + [0])
    end_wrong = tuple(range(1, R*C-2) + [R*C-1, R*C-2, 0])
    expected = {(C*i+j+1) % (R*C) : (i, j)
                for i in xrange(R) for j in xrange(C)}

    min_heap = [(0, 0, begin.index(0), begin)]
    lookup = {begin: 0}
    while min_heap:
        f, g, zero, board = heapq.heappop(min_heap)
        if board == end: return g
        if board == end_wrong: return -1
        if f > lookup[board]: continue

        r, c = divmod(zero, C)
        for direction in ((-1, 0), (1, 0), (0, -1), (0, 1)):
            i, j = r+direction[0], c+direction[1]
            if 0 <= i < R and 0 <= j < C:
                new_zero = C*i+j
                tmp = list(board)
                tmp[zero], tmp[new_zero] = tmp[new_zero], tmp[zero]
                new_board = tuple(tmp)
                f = g+1+heuristic_estimate(new_board, R, C, expected)
                if f < lookup.get(new_board, float("inf")):
                    lookup[new_board] = f
                    heapq.heappush(min_heap, (f, g+1, new_zero, new_board))
    return -1



