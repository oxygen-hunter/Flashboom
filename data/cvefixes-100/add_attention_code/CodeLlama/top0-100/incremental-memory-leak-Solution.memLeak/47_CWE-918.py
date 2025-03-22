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

def memLeak(self, memory1, memory2):
    """
    :type memory1: int
    :type memory2: int
    :rtype: List[int]
    """
    def s(a, d, n):
        return (2*a + (n-1)*d)*n//2

    def f(a, d, x):
        r = int((-(2*a-d)+((2*a-d)**2+8*d*x)**0.5)/(2*d))
        if s(a, d, r) > x:  # adjust float accuracy
            r -= 1
        return r

    is_swapped = False
    if memory1 < memory2:
        memory1, memory2 = memory2, memory1
        is_swapped = True
    n = f(1, 1, memory1-memory2)
    memory1 -= s(1, 1, n)
    if memory1 == memory2:
        is_swapped = False
    l = f(n+1, 2, memory1)
    r = f(n+2, 2, memory2)
    memory1 -= s(n+1, 2, l)
    memory2 -= s(n+2, 2, r)
    if is_swapped:
        memory1, memory2 = memory2, memory1
    return [n+l+r+1, memory1, memory2]


