def publisher_list():
    if current_user.get_view_property('publisher', 'dir') == 'desc':
        order = db.Publishers.name.desc()
        order_no = 0
    else:
        order = db.Publishers.name.asc()
        order_no = 1
    if current_user.check_visibility(constants.SIDEBAR_PUBLISHER):
        entries = calibre_db.session.query(db.Publishers, func.count('books_publishers_link.book').label('count')) \
            .join(db.books_publishers_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_publishers_link.publisher')).order_by(order).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Publishers.name, 1, 1)).label('char')) \
            .join(db.books_publishers_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Publishers.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Publishers"), page="publisherlist", data="publisher", order=order_no)
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


