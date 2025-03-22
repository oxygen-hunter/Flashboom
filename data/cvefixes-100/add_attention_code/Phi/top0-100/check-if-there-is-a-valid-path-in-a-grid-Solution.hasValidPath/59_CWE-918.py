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

def hasValidPath(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: bool
    """
    E, S, W, N = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    directions = [
        [W, E], [N, S],
        [W, S], [S, E],
        [W, N], [N, E]
    ]

    for r, c in directions[grid[0][0]-1]:
        if not (0 <= r < len(grid) and 0 <= c < len(grid[0])):
            continue
        pr, pc = 0, 0
        while r != len(grid)-1 or c != len(grid[0])-1:
            for dx, dy in directions[grid[r][c]-1]:
                nr, nc = r+dx, c+dy
                if (nr == pr and nc == pc) or \
                   not(0 <= nr < len(grid) and 0 <= nc < len(grid[0])) or \
                   (-dx, -dy) not in directions[grid[nr][nc]-1]:
                    continue
                pr, pc, r, c = r, c, nr, nc
                break
            else:
                return False
        return True
    return len(grid) == len(grid[0]) == 1 


