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

def canMakePalindromeQueries(self, s, queries):
    """
    :type s: str
    :type queries: List[List[int]]
    :rtype: List[bool]
    """
    def check(left1, right1, left2, right2):
        def same(left, right):
            return all(prefixs1[right+1][i]-prefixs1[left][i] == prefixs2[right+1][i]-prefixs2[left][i] for i in xrange(26))

        min_left, max_left = min(left1, left2), max(left1, left2)
        min_right, max_right = min(right1, right2), max(right1, right2)
        if not (prefix[min_left]-prefix[0] == prefix[-1]-prefix[max_right+1] == 0):
            return False
        if min_right < max_left:  # non-overlapped
            return prefix[max_left]-prefix[min_right+1] == 0 and same(min_left, min_right) and same(max_left, max_right)
        # overlapped
        if (left1 == min_left) == (right1 == max_right):  # inside another
            return same(min_left, max_right)
        # not inside another
        p1, p2 = (prefixs1, prefixs2) if min_left == left1 else (prefixs2, prefixs1)
        diff1 = [(p1[min_right+1][i]-p1[min_left][i])-(p2[max_left][i]-p2[min_left][i]) for i in xrange(26)]
        diff2 = [(p2[max_right+1][i]-p2[max_left][i])-(p1[max_right+1][i]-p1[min_right+1][i]) for i in xrange(26)]
        return diff1 == diff2 and all(x >= 0 for x in diff1)  # test case: s = "aabbba", queries = [[0,1,3,4]]

    prefix = [0]*(len(s)//2+1)
    prefixs1 = [[0]*26 for _ in xrange(len(s)//2+1)]
    prefixs2 = [[0]*26 for _ in xrange(len(s)//2+1)]
    for i in xrange(len(s)//2):
        x, y = ord(s[i])-ord('a'), ord(s[~i])-ord('a')
        prefix[i+1] = prefix[i]+int(x != y)
        for j in xrange(26):
            prefixs1[i+1][j] = prefixs1[i][j]+int(j == x)
            prefixs2[i+1][j] = prefixs2[i][j]+int(j == y)
    return [check(q[0], q[1], (len(s)-1)-q[3], (len(s)-1)-q[2]) for q in queries]


