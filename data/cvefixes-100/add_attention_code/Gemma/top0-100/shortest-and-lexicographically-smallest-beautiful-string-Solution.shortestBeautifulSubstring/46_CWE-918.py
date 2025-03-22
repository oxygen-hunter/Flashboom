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

def shortestBeautifulSubstring(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: str
    """
    def check(r1, r2):
        if r1[1]-r1[0]+1 > r2[1]-r2[0]+1:
            return False
        if r1[1]-r1[0]+1 < r2[1]-r2[0]+1:
            return True
        for i, j in itertools.izip(xrange(r1[0], r1[1]+1), xrange(r2[0], r2[1]+1)):
            if s[i] != s[j]:
                return s[i] < s[j]
        return False

    result = []
    left = curr = 0
    for right in xrange(len(s)):
        curr += s[right] == '1'
        while curr == k+1:
            curr -= s[left] == '1'
            left += 1
        while left < len(s) and s[left] == '0':
            left += 1
        if curr == k:
            if not result or check([left, right], result):
                result = [left, right]
    return s[result[0]:result[1]+1] if result else ""


