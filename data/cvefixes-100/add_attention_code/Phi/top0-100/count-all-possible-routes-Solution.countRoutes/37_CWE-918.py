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

def countRoutes(self, locations, start, finish, fuel):
    """
    :type locations: List[int]
    :type start: int
    :type finish: int
    :type fuel: int
    :rtype: int
    """
    MOD = 10**9+7

    s, f = locations[start], locations[finish]
    locations.sort()
    start, finish = bisect.bisect_left(locations, s), bisect.bisect_left(locations, f)

    left = [[0]*(fuel+1) for _ in xrange(len(locations))]  # left[i][f], last move is toward left to location i by f fuel
    right = [[0]*(fuel+1) for _ in xrange(len(locations))]  # right[i][f], last move is toward right to location i by f fuel
    for f in xrange(1, fuel+1):
        for j in xrange(len(locations)-1):
            d = locations[j+1]-locations[j]
            if f > d:
                # left[j][f] = right[j+1][f-d(j, j+1)] + 2*right[j+2][f-d(j, j+2)] + ... + 2^(k-1)*right[j+k][f-d(j, j+k)]
                # => left[j+1][f] = (ight[j+2][f-d(j+1, j+2)] + 2*right[j+3][f-d(j+1, j+3)] + ... + 2^(k-2)*right[j+1+k-1][f-d(j+1, j+1+k-1)]
                # => left[j+1][f-d(j, j+1)] = right[j+2][f-d(j, j+2)] + 2*right[j+3][f-d(j, j+3)] + ... + 2^(k-2)*right[j+k][f-d(j, j+k)]
                # => left[j][f] = right[j+1][f-d(j, j+1)] + 2*left[j+1][f-d(j, j+1)]
                left[j][f] = (right[j+1][f-d] + 2*left[j+1][f-d] % MOD) % MOD
            elif f == d:
                left[j][f] = int(j+1 == start)
        for j in xrange(1, len(locations)):
            d = locations[j]-locations[j-1]
            if f > d:
                # right[j][f] = left[j-1][f-d(j, j-1)] + 2*left[j-2][f-d(j, j-2)] + ... + 2^(k-1)*left[j-k][f-d(j, j-k)]
                # => right[j-1][f] = left[j-2][f-d(j-1, j-2)] + 2*left[j-3][f-d(j-1, j-3)] + ... + 2^(k-2)*left[j-1-k+1][f-d(j-1, j-1-k+1)]
                # => right[j-1][f-d(j, j-1)] = left[j-2][f-d(j, j-2)] + 2*left[j-3][f-d(j, j-3)] + ... + 2^(k-2)*left[j-k][f-d(j, j-k)]
                # => right[j][f] = left[j-1][f-d(j, j-1)] + 2*right[j-1][f-d(j, j-1)]
                right[j][f] = (left[j-1][f-d] + 2*right[j-1][f-d] % MOD) % MOD
            elif f == d:
                right[j][f] = int(j-1 == start)
    result = int(start == finish)
    for f in xrange(1, fuel+1):
        result = ((result + left[finish][f]) % MOD + right[finish][f]) % MOD
    return result



