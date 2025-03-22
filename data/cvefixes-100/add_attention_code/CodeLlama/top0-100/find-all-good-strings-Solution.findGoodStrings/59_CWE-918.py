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

def findGoodStrings(self, n, s1, s2, evil):
    """
    :type n: int
    :type s1: str
    :type s2: str
    :type evil: str
    :rtype: int
    """
    MOD = 10**9+7
    def getPrefix(pattern):
        prefix = [-1]*len(pattern)
        j = -1
        for i in xrange(1, len(pattern)):
            while j != -1 and pattern[j+1] != pattern[i]:
                j = prefix[j]
            if pattern[j+1] == pattern[i]:
                j += 1
            prefix[i] = j
        return prefix

    prefix = getPrefix(evil)
    dp = [[[[0]*len(evil) for _ in xrange(2)] for _ in xrange(2)] for _ in xrange(2)]
    dp[0][0][0][0] = 1
    for i in xrange(n):
        dp[(i+1)%2] = [[[0]*len(evil) for _ in xrange(2)] for _ in xrange(2)]
        for j in xrange(2):
            for k in xrange(2):
                min_c = 'a' if j else s1[i]
                max_c = 'z' if k else s2[i]
                for l in xrange(len(evil)):
                    if not dp[i%2][j][k][l]:
                        continue
                    for c in xrange(ord(min_c)-ord('a'), ord(max_c)-ord('a')+1):
                        c = chr(c+ord('a'))
                        m = l-1
                        while m != -1 and evil[m+1] != c:
                            m = prefix[m]
                        if evil[m+1] == c:
                            m += 1
                        if m+1 == len(evil):
                            continue
                        dp[(i+1)%2][j or (s1[i] != c)][k or (s2[i] != c)][m+1] = \
                            (dp[(i+1)%2][j or (s1[i] != c)][k or (s2[i] != c)][m+1] + dp[i%2][j][k][l]) % MOD
    result = 0
    for j in xrange(2):
        for k in xrange(2):
            for l in xrange(len(evil)):
                result = (result + dp[n%2][j][k][l]) % MOD
    return result


