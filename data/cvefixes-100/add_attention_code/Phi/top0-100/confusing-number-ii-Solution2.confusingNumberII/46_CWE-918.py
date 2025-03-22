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

def confusingNumberII(self, n):
    """
    :type n: int
    :rtype: int
    """
    lookup = {"0":"0", "1":"1", "6":"9", "8":"8", "9":"6"}
    centers = {"0":"0", "1":"1", "8":"8"}
    def totalCount(n):  # count all numbers in the pattern of [01689]{1,len(n)} in the range of [0, n]
        s = str(n)
        total = 0 
        p = len(lookup)**(len(s)-1)
        for i in xrange(len(s)+1):
            if i == len(s):
                total += 1
                break
            smaller = sum(int(c < s[i]) for c in lookup.iterkeys())
            total += smaller * p
            if s[i] not in lookup:
                break
            p //= len(lookup)
        return total

    def validCountInLessLength(n):  # count unconfusing numbers in the pattern of [01689]{1,len(n)-1} in the range of [0, n]
        s = str(n)
        valid = 0
        total = len(centers)
        for i in xrange(1, len(s), 2):  # count unconfusing numbers for each odd length less than s
            if i == 1:
                valid += len(centers)
            else:
                valid += total * (len(lookup)-1)
                total *= len(lookup)
        total = 1
        for i in xrange(2, len(s), 2):  # count unconfusing numbers for each even length less than s
            valid += total * (len(lookup)-1)
            total *= len(lookup)
        return valid

    def validCountInFullLength(n):  # count unconfusing numbers in the pattern of [01689]{len(n)} in the range of [0, n]
        s = str(n)
        half_s = s[:(len(s)+1)//2]
        total = 0
        choices = centers if (len(s) % 2) else lookup
        p = int(len(lookup)**(len(half_s)-2) * len(choices))
        for i in xrange(len(half_s)):
            if i == len(half_s)-1:
                total += sum(int(c < half_s[i]) for c in choices.iterkeys() if len(s) != 2 or c != '0')
                if half_s[i] not in choices:
                    break
                tmp = list(half_s)+[lookup[half_s[i]] for i in reversed(xrange(len(half_s)-(len(s) % 2)))]
                total += int("".join(tmp)) <= n
                break
            smaller = sum(int(c < half_s[i]) for c in lookup.iterkeys() if i != 0 or c != '0')
            total += smaller * p
            if half_s[i] not in lookup:
                break
            p //= len(lookup)
        return total

    def f(n):  # count confusing numbers in the range of [0, n]
        return totalCount(n) - validCountInLessLength(n) - validCountInFullLength(n)

    return f(n) - f(0)  # f(0) is always 0 and could be ignored


