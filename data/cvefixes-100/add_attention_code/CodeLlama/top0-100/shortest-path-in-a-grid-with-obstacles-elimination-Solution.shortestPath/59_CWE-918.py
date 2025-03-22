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

def shortestPath(self, grid, k):
    """
    :type grid: List[List[int]]
    :type k: int
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    def dot(a, b):
        return a[0]*b[0]+a[1]*b[1]

    def g(a, b):
        return abs(a[0]-b[0])+abs(a[1]-b[1])
    
    def a_star(grid, b, t, k):
        f, dh = g(b, t), 2
        closer, detour = [(b, k)], []
        lookup = {}
        while closer or detour:
            if not closer:
                f += dh
                closer, detour = detour, closer
            b, k = closer.pop()
            if b == t:
                return f
            if b in lookup and lookup[b] >= k:
                continue
            lookup[b] = k
            for dx, dy in directions:
                nb = (b[0]+dx, b[1]+dy)
                if not (0 <= nb[0] < len(grid) and 0 <= nb[1] < len(grid[0]) and
                        (grid[nb[0]][nb[1]] == 0 or k > 0) and
                        (nb not in lookup or lookup[nb] < k)):
                    continue
                (closer if dot((dx, dy), (t[0]-b[0], t[1]-b[1])) > 0 else detour).append((nb, k-int(grid[nb[0]][nb[1]] == 1)))
        return -1

    return a_star(grid, (0, 0), (len(grid)-1, len(grid[0])-1), k)


