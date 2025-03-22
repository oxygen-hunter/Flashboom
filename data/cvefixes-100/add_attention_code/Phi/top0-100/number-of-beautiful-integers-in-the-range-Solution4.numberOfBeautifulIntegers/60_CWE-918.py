def show_book(book_id):
    entries = calibre_db.get_book_read_archived(book_id, config.config_read_column, allow_show_archived=True)
    if entries:
        read_book = entries[1]
        archived_book = entries[2]
        entry = entries[0]
        entry.read_status = read_book == ub.ReadBook.STATUS_FINISHED
        entry.is_archived = archived_book
        for index in range(0, len(entry.languages)):
            entry.languages[index].language_name = isoLanguages.get_language_name(get_locale(), entry.languages[
                index].lang_code)
        cc = get_cc_columns(filter_config_custom_read=True)
        book_in_shelfs = []
        shelfs = ub.session.query(ub.BookShelf).filter(ub.BookShelf.book_id == book_id).all()
        for sh in shelfs:
            book_in_shelfs.append(sh.shelf)

        entry.tags = sort(entry.tags, key=lambda tag: tag.name)

        entry.ordered_authors = calibre_db.order_authors([entry])

        entry.kindle_list = check_send_to_kindle(entry)
        entry.reader_list = check_read_formats(entry)

        entry.audioentries = []
        for media_format in entry.data:
            if media_format.format.lower() in constants.EXTENSIONS_AUDIO:
                entry.audioentries.append(media_format.format.lower())

        return render_title_template('detail.html',
                                     entry=entry,
                                     cc=cc,
                                     is_xhr=request.headers.get('X-Requested-With')=='XMLHttpRequest',
                                     title=entry.title,
                                     books_shelfs=book_in_shelfs,
                                     page="book")
    else:
        log.debug(u"Oops! Selected book title is unavailable. File does not exist or is not accessible")
        flash(_(u"Oops! Selected book title is unavailable. File does not exist or is not accessible"),
              category="error")
        return redirect(url_for("web.index"))

def numberOfBeautifulIntegers(self, low, high, k):
    """
    :type low: int
    :type high: int
    :type k: int
    :rtype: int
    """
    def f(x):
        digits = map(int, str(x))
        dp = [[[[0]*k for _ in xrange(2*len(digits)+1)] for _ in xrange(2)] for _ in xrange(2)]
        for tight in xrange(2):
            dp[0][tight][0][0] = 1
        for i in reversed(xrange(len(digits))):
            new_dp = [[[[0]*k for _ in xrange(2*len(digits)+1)] for _ in xrange(2)] for _ in xrange(2)]
            for zero in xrange(2):
                for tight in xrange(2):
                    for d in xrange((digits[i] if tight else 9)+1):
                        new_zero = int(zero and d == 0)
                        new_tight = int(tight and d == digits[i])
                        for diff in xrange(-len(digits), len(digits)+1):
                            new_diff = diff+((1 if d%2 == 0 else -1) if new_zero == 0 else 0)
                            for total in xrange(k):
                                new_total = (total*10+d)%k
                                new_dp[zero][tight][diff][total] += dp[new_zero][new_tight][new_diff][new_total]
            dp = new_dp
        return dp[1][1][0][0]

    return f(high)-f(low-1)


