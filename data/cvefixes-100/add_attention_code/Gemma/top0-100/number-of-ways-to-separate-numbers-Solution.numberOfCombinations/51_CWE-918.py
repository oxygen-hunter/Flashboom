def render_read_books(page, are_read, as_xml=False, order=None):
    sort_param = order[0] if order else []
    if not config.config_read_column:
        if are_read:
            db_filter = and_(ub.ReadBook.user_id == int(current_user.id),
                             ub.ReadBook.read_status == ub.ReadBook.STATUS_FINISHED)
        else:
            db_filter = coalesce(ub.ReadBook.read_status, 0) != ub.ReadBook.STATUS_FINISHED
        entries, random, pagination = calibre_db.fill_indexpage(page, 0,
                                                                db.Books,
                                                                db_filter,
                                                                sort_param,
                                                                False, 0,
                                                                db.books_series_link,
                                                                db.Books.id == db.books_series_link.c.book,
                                                                db.Series,
                                                                ub.ReadBook, db.Books.id == ub.ReadBook.book_id)
    else:
        try:
            if are_read:
                db_filter = db.cc_classes[config.config_read_column].value == True
            else:
                db_filter = coalesce(db.cc_classes[config.config_read_column].value, False) != True
            entries, random, pagination = calibre_db.fill_indexpage(page, 0,
                                                                    db.Books,
                                                                    db_filter,
                                                                    sort_param,
                                                                    False, 0,
                                                                    db.books_series_link,
                                                                    db.Books.id == db.books_series_link.c.book,
                                                                    db.Series,
                                                                    db.cc_classes[config.config_read_column])
        except (KeyError, AttributeError):
            log.error("Custom Column No.%d is not existing in calibre database", config.config_read_column)
            if not as_xml:
                flash(_("Custom Column No.%(column)d is not existing in calibre database",
                        column=config.config_read_column),
                      category="error")
                return redirect(url_for("web.index"))
            return [] # ToDo: Handle error Case for opds

    if as_xml:
        return entries, pagination
    else:
        if are_read:
            name = _(u'Read Books') + ' (' + str(pagination.total_count) + ')'
            pagename = "read"
        else:
            name = _(u'Unread Books') + ' (' + str(pagination.total_count) + ')'
            pagename = "unread"
        return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                     title=name, page=pagename, order=order[1])

def numberOfCombinations(self, num):
    """
    :type num: str
    :rtype: int
    """
    MOD = 10**9+7
    def find_longest_common_prefix(num):
        lcp = [[0]*(len(num)+1) for _ in xrange(len(num)+1)]  # lcp[i][j]: longest length of the common prefix which starts at num[i], num[j]
        for i in reversed(xrange(len(lcp)-1)):
            for j in reversed(xrange(len(lcp[0])-1)):
                if num[i] == num[j]:
                    lcp[i][j] = lcp[i+1][j+1]+1
        return lcp

    def is_less_or_equal_to_with_same_length(num, lcp, i, j, l):
        return lcp[i][j] >= l or num[i+lcp[i][j]] < num[j+lcp[i][j]]

    lcp = find_longest_common_prefix(num)
    dp = [[0]*len(num) for _ in xrange(len(num))]  # dp[i][l]: the count of numbers ending at num[i], where the length of the last number is l+1
    dp[0][0] = int(num[0] != '0')
    for i in xrange(1, len(num)):
        dp[i][i] = dp[i-1][i-1]
        if num[i] == '0':
            continue
        accu = 0
        for l in xrange(len(num)-i+1):
            ni = i+l-1
            dp[ni][l-1] = accu  # accumulated count where the length of the second to last number ending at num[i-1] is shorter than the length of the last number ending at num[i+l-1]
            if i-l < 0:
                continue
            if num[i-l] != '0' and is_less_or_equal_to_with_same_length(num, lcp, i-l, i, l):
                dp[ni][l-1] = (dp[ni][l-1] + dp[i-1][l-1]) % MOD
            accu = (accu + dp[i-1][l-1]) % MOD
    return reduce(lambda total, x: (total+x)%MOD, dp[-1], 0)


