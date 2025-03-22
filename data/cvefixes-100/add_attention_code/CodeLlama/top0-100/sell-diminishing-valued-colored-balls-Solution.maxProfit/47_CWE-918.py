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

def maxProfit(self, inventory, orders):
    """
    :type inventory: List[int]
    :type orders: int
    :rtype: int
    """
    MOD = 10**9+7
    def check(inventory, orders, x):
        return count(inventory, x) > orders
    
    def count(inventory, x):
        return sum(count-x+1 for count in inventory if count >= x)

    left, right = 1, max(inventory)
    while left <= right:
        mid = left + (right-left)//2
        if not check(inventory, orders, mid):
            right = mid-1
        else:
            left = mid+1
    # assert(orders-count(inventory, left) >= 0)
    return (sum((left+cnt)*(cnt-left+1)//2 for cnt in inventory if cnt >= left) +
            (left-1)*(orders-count(inventory, left)))% MOD


