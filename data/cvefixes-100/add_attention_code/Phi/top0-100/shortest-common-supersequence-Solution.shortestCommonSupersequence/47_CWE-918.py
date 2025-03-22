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

def shortestCommonSupersequence(self, str1, str2):
    """
    :type str1: str
    :type str2: str
    :rtype: str
    """
    dp = [[0 for _ in xrange(len(str2)+1)] for _ in xrange(2)]
    bt = [[None for _ in xrange(len(str2)+1)] for _ in xrange(len(str1)+1)]
    for i, c in enumerate(str1):
        bt[i+1][0] = (i, 0, c)
    for j, c in enumerate(str2):
        bt[0][j+1] = (0, j, c)
    for i in xrange(len(str1)):
        for j in xrange(len(str2)):
            if dp[i % 2][j+1] > dp[(i+1) % 2][j]:
                dp[(i+1) % 2][j+1] = dp[i % 2][j+1]
                bt[i+1][j+1] = (i, j+1, str1[i])
            else:
                dp[(i+1) % 2][j+1] = dp[(i+1) % 2][j]
                bt[i+1][j+1] = (i+1, j, str2[j])
            if str1[i] != str2[j]:
                continue
            if dp[i % 2][j]+1 > dp[(i+1) % 2][j+1]:
                dp[(i+1) % 2][j+1] = dp[i % 2][j]+1
                bt[i+1][j+1] = (i, j, str1[i])
    
    i, j = len(str1), len(str2)
    result = []
    while i != 0 or j != 0:
        i, j, c = bt[i][j]
        result.append(c)
    result.reverse()
    return "".join(result)


