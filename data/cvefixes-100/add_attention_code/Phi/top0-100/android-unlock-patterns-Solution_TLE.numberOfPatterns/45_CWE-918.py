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

    def contain(used, i):
        return bool(used & (1 << i))

    def convert(i, j):
        return 3 * i + j

    def numberOfPatternsHelper(m, n, level, used, i):
        number = 0
        if level > n:
            return number

        if m <= level <= n:
            number += 1

        x1, y1 = divmod(i, 3)
        for j in xrange(9):
            if contain(used, j):
                continue

            x2, y2 = divmod(j, 3)
            if ((x1 == x2 and abs(y1 - y2) == 2) or
                (y1 == y2 and abs(x1 - x2) == 2) or
                (abs(x1 - x2) == 2 and abs(y1 - y2) == 2)) and \
               not contain(used,
                           convert((x1 + x2) // 2, (y1 + y2) // 2)):
                    continue

            number += numberOfPatternsHelper(m, n, level + 1, merge(used, j), j)

        return number

    number = 0
    # 1, 3, 7, 9
    number += 4 * numberOfPatternsHelper(m, n, 1, merge(0, 0), 0)
    # 2, 4, 6, 8
    number += 4 * numberOfPatternsHelper(m, n, 1, merge(0, 1), 1)
    # 5
    number += numberOfPatternsHelper(m, n, 1, merge(0, 4), 4)
    return number



