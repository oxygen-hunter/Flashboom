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

def isMatch(self, s, p):
    p_ptr, s_ptr, last_s_ptr, last_p_ptr = 0, 0, -1, -1
    last_ptr = []
    while s_ptr < len(s):
        if p_ptr < len(p) and (p_ptr == len(p) - 1 or p[p_ptr + 1] != '*') and \
        (s_ptr < len(s) and (p[p_ptr] == s[s_ptr] or p[p_ptr] == '.')):
                s_ptr += 1
                p_ptr += 1
        elif p_ptr < len(p) - 1 and (p_ptr != len(p) - 1 and p[p_ptr + 1] == '*'):
            p_ptr += 2
            last_ptr.append([s_ptr, p_ptr])
        elif  last_ptr:
            [last_s_ptr, last_p_ptr] = last_ptr.pop()
            while last_ptr and p[last_p_ptr - 2] != s[last_s_ptr] and p[last_p_ptr - 2] != '.':
                [last_s_ptr, last_p_ptr] = last_ptr.pop()

            if p[last_p_ptr - 2] == s[last_s_ptr] or p[last_p_ptr - 2] == '.':
                last_s_ptr += 1
                s_ptr = last_s_ptr
                p_ptr = last_p_ptr
                last_ptr.append([s_ptr, p_ptr])
            else:
                return False
        else:
            return False

    while p_ptr < len(p) - 1 and p[p_ptr] == '.' and p[p_ptr + 1] == '*':
        p_ptr += 2

    return p_ptr == len(p)



