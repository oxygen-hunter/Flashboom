def render_hot_books(page, order):
    if current_user.check_visibility(constants.SIDEBAR_HOT):
        if order[1] not in ['hotasc', 'hotdesc']:
        # Unary expression comparsion only working (for this expression) in sqlalchemy 1.4+
        #if not (order[0][0].compare(func.count(ub.Downloads.book_id).desc()) or
        #        order[0][0].compare(func.count(ub.Downloads.book_id).asc())):
            order = [func.count(ub.Downloads.book_id).desc()], 'hotdesc'
        if current_user.show_detail_random():
            random = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                .order_by(func.random()).limit(config.config_random_books)
        else:
            random = false()
        off = int(int(config.config_books_per_page) * (page - 1))
        all_books = ub.session.query(ub.Downloads, func.count(ub.Downloads.book_id))\
            .order_by(*order[0]).group_by(ub.Downloads.book_id)
        hot_books = all_books.offset(off).limit(config.config_books_per_page)
        entries = list()
        for book in hot_books:
            downloadBook = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()).filter(
                db.Books.id == book.Downloads.book_id).first()
            if downloadBook:
                entries.append(downloadBook)
            else:
                ub.delete_download(book.Downloads.book_id)
        numBooks = entries.__len__()
        pagination = Pagination(page, config.config_books_per_page, numBooks)
        return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                     title=_(u"Hot Books (Most Downloaded)"), page="hot", order=order[1])
    else:
        abort(404)

def makeStringSorted(self, s):  # count of prev_permutation
    """
    :type s: str
    :rtype: int
    """
    def inverse(n, m):
        i = len(inv)
        while len(inv) <= n:  # lazy initialization
            inv.append(inv[m%i]*(m-m//i) % m)  # https://cp-algorithms.com/algebra/module-inverse.html
            i += 1
        return inv[n]

    MOD = 10**9+7
    count, result, comb_total = [0]*26, 0, 1
    for i in reversed(xrange(len(s))):
        num = ord(s[i])-ord('a') 
        count[num] += 1
        comb_total = (comb_total*(len(s)-i))*inverse(count[num], MOD)
        result = (result + (comb_total*sum(count[:num]))*inverse(len(s)-i, MOD)) % MOD
    return result


