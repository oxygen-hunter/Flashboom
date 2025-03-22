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

def executeInstructions(self, n, startPos, s):
    """
    :type n: int
    :type startPos: List[int]
    :type s: str
    :rtype: List[int]
    """
    directions = {'U':(-1, 0), 'R':(0, 1), 'D':(1, 0), 'L':(0, -1)}
    (x0, y0), (x, y) = startPos, (0, 0)
    result = range(len(s), 0, -1)
    lookup_x = collections.defaultdict(list)
    lookup_y = collections.defaultdict(list)
    lookup_x[x0-x].append(0)
    lookup_y[y0-y].append(0)
    for i, d in enumerate(s):
        dx, dy = directions[d]
        x, y = x+dx, y+dy
        for k in n-x, -x-1:
            if k not in lookup_x:
                continue
            for j in lookup_x[k]:
                result[j] = min(result[j], i-j)
            lookup_x[k] = []
        for k in n-y, -y-1:
            if k not in lookup_y:
                continue
            for j in lookup_y[k]:
                result[j] = min(result[j], i-j)
            lookup_y[k] = []
        lookup_x[x0-x].append(i+1)
        lookup_y[y0-y].append(i+1)
    return result


