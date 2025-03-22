def render_downloaded_books(page, order, user_id):
    if current_user.role_admin():
        user_id = int(user_id)
    else:
        user_id = current_user.id
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD):
        if current_user.show_detail_random():
            random = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                .order_by(func.random()).limit(config.config_random_books)
        else:
            random = false()

        entries, __, pagination = calibre_db.fill_indexpage(page,
                                                            0,
                                                            db.Books,
                                                            ub.Downloads.user_id == user_id,
                                                            order[0],
                                                            False, 0,
                                                            db.books_series_link,
                                                            db.Books.id == db.books_series_link.c.book,
                                                            db.Series,
                                                            ub.Downloads, db.Books.id == ub.Downloads.book_id)
        for book in entries:
            if not calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                             .filter(db.Books.id == book.id).first():
                ub.delete_download(book.id)
        user = ub.session.query(ub.User).filter(ub.User.id == user_id).first()
        return render_title_template('index.html',
                                     random=random,
                                     entries=entries,
                                     pagination=pagination,
                                     id=user_id,
                                     title=_(u"Downloaded books by %(user)s",user=user.name),
                                     page="download",
                                     order=order[1])
    else:
        abort(404)

def minimumCost(self, sentence, k):
    """
    :type sentence: str
    :type k: int
    :rtype: int
    """
    word_lens = []
    j = 0
    for i in xrange(len(sentence)+1):
        if i != len(sentence) and sentence[i] != ' ':
            continue
        word_lens.append(i-j)
        j = i+1
    dp = [float("inf")]*(1+(len(word_lens)-1))  # dp[i]: min cost of the first i word_lens where i in [0, len(words)-1]
    dp[0] = 0
    for i in xrange(1, (len(word_lens)-1)+1):
        total = word_lens[i-1]
        for j in reversed(xrange(i)):
            dp[i] = min(dp[i], dp[j] + (k-total)**2)
            if j-1 < 0:
                continue
            total += (word_lens[j-1]+1)
            if total > k:
                break
    i, total = len(word_lens)-1, -1
    while i >= 0 and total + (word_lens[i]+1) <= k:  # find max i s.t. the length of the last line > k
        total += (word_lens[i]+1)
        i -= 1
    return min(dp[j] for j in xrange(i+1, len(dp)))


