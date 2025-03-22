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

def numberOfPatterns(self, m, n):
    """
    :type m: int
    :type n: int
    :rtype: int
    """
    def merge(used, i):
        return used | (1 << i)

    def number_of_keys(i):
        number = 0
        while i > 0:
            i &= i - 1
            number += 1
        return number

    def exclude(used, i):
        return used & ~(1 << i)

    def contain(used, i):
        return bool(used & (1 << i))

    def convert(i, j):
        return 3 * i + j

    # dp[i][j]: i is the set of the numbers in binary representation,
    #            d[i][j] is the number of ways ending with the number j.
    dp = [[0] * 9 for _ in xrange(1 << 9)]
    for i in xrange(9):
        dp[merge(0, i)][i] = 1

    res = 0
    for used in xrange(len(dp)):
        number = number_of_keys(used)
        if number > n:
            continue

        for i in xrange(9):
            if not contain(used, i):
                continue

            x1, y1 = divmod(i, 3)
            for j in xrange(9):
                if i == j or not contain(used, j):
                    continue

                x2, y2 = divmod(j, 3)
                if ((x1 == x2 and abs(y1 - y2) == 2) or
                    (y1 == y2 and abs(x1 - x2) == 2) or
                    (abs(x1 - x2) == 2 and abs(y1 - y2) == 2)) and \
                   not contain(used,
                               convert((x1 + x2) // 2, (y1 + y2) // 2)):
                        continue

                dp[used][i] += dp[exclude(used, i)][j]

            if m <= number <= n:
                res += dp[used][i]

    return res



