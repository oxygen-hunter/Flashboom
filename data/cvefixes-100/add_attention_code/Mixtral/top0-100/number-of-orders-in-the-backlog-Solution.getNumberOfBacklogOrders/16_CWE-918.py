def category_list():
    if current_user.check_visibility(constants.SIDEBAR_CATEGORY):
        if current_user.get_view_property('category', 'dir') == 'desc':
            order = db.Tags.name.desc()
            order_no = 0
        else:
            order = db.Tags.name.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Tags, func.count('books_tags_link.book').label('count')) \
            .join(db.books_tags_link).join(db.Books).order_by(order).filter(calibre_db.common_filters()) \
            .group_by(text('books_tags_link.tag')).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Tags.name, 1, 1)).label('char')) \
            .join(db.books_tags_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Tags.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Categories"), page="catlist", data="category", order=order_no)
    else:
        abort(404)

def getNumberOfBacklogOrders(self, orders):
    """
    :type orders: List[List[int]]
    :rtype: int
    """
    MOD = 10**9 + 7
    buy, sell  = [], []  # max_heap, min_heap
    for p, a, t in orders:
        if t == 0:
            heapq.heappush(buy, [-p, a])
        else:
            heapq.heappush(sell, [p, a])
        while sell and buy and sell[0][0] <= -buy[0][0]:
            k = min(buy[0][1], sell[0][1])
            tmp = heapq.heappop(buy)
            tmp[1] -= k
            if tmp[1]:
                heapq.heappush(buy, tmp)
            tmp = heapq.heappop(sell)
            tmp[1] -= k
            if tmp[1]:
                heapq.heappush(sell, tmp)
    return reduce(lambda x, y: (x+y) % MOD, (a for _, a in buy + sell))


