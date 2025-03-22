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

def strongPasswordChecker(self, s):
    """
    :type s: str
    :rtype: int
    """
    missing_type_cnt = 3
    if any('a' <= c <= 'z' for c in s):
        missing_type_cnt -= 1
    if any('A' <= c <= 'Z' for c in s):
        missing_type_cnt -= 1
    if any(c.isdigit() for c in s):
        missing_type_cnt -= 1

    total_change_cnt = 0
    one_change_cnt, two_change_cnt, three_change_cnt = 0, 0, 0
    i = 2
    while i < len(s):
        if s[i] == s[i-1] == s[i-2]:
            length = 2
            while i < len(s) and s[i] == s[i-1]:
                length += 1
                i += 1

            total_change_cnt += length / 3
            if length % 3 == 0:
                one_change_cnt += 1
            elif length % 3 == 1:
                two_change_cnt += 1
            else:
                three_change_cnt += 1
        else:
            i += 1

    if len(s) < 6:
        return max(missing_type_cnt, 6 - len(s))
    elif len(s) <= 20:
        return max(missing_type_cnt, total_change_cnt)
    else:
        delete_cnt = len(s) - 20

        total_change_cnt -= min(delete_cnt, one_change_cnt * 1) / 1
        total_change_cnt -= min(max(delete_cnt - one_change_cnt, 0), two_change_cnt * 2) / 2
        total_change_cnt -= min(max(delete_cnt - one_change_cnt - 2 * two_change_cnt, 0), three_change_cnt * 3) / 3

        return delete_cnt + max(missing_type_cnt, total_change_cnt)



