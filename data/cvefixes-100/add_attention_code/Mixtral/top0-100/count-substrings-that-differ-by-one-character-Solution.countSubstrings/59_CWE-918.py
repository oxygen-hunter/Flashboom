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

def countSubstrings(self, s, t):
    """
    :type s: str
    :type t: str
    :rtype: int
    """
    def count(i, j):  # for each possible alignment, count the number of substrs that differ by 1 char
        result = left_cnt = right_cnt = 0  # left and right consecutive same counts relative to the different char
        for k in xrange(min(len(s)-i, len(t)-j)):
            right_cnt += 1
            if s[i+k] != t[j+k]:
                left_cnt, right_cnt = right_cnt, 0
                # prev_i = i+k-prev+1
            result += left_cnt  # target substrs are [s[left_i+c:i+k+1] for c in xrange(left_cnt)]
        return result

    return sum(count(i, 0) for i in xrange(len(s))) + \
           sum(count(0, j) for j in xrange(1, len(t)))


