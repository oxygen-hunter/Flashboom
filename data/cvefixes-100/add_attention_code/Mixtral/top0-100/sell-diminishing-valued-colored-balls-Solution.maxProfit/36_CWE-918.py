def ratings_list():
    if current_user.check_visibility(constants.SIDEBAR_RATING):
        if current_user.get_view_property('ratings', 'dir') == 'desc':
            order = db.Ratings.rating.desc()
            order_no = 0
        else:
            order = db.Ratings.rating.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Ratings, func.count('books_ratings_link.book').label('count'),
                                   (db.Ratings.rating / 2).label('name')) \
            .join(db.books_ratings_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_ratings_link.rating')).order_by(order).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=list(),
                                     title=_(u"Ratings list"), page="ratingslist", data="ratings", order=order_no)
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


