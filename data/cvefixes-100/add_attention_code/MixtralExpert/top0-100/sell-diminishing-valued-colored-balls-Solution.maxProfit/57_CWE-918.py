def set_bookmark(book_id, book_format):
    bookmark_key = request.form["bookmark"]
    ub.session.query(ub.Bookmark).filter(and_(ub.Bookmark.user_id == int(current_user.id),
                                              ub.Bookmark.book_id == book_id,
                                              ub.Bookmark.format == book_format)).delete()
    if not bookmark_key:
        ub.session_commit()
        return "", 204

    lbookmark = ub.Bookmark(user_id=current_user.id,
                            book_id=book_id,
                            format=book_format,
                            bookmark_key=bookmark_key)
    ub.session.merge(lbookmark)
    ub.session_commit("Bookmark for user {} in book {} created".format(current_user.id, book_id))
    return "", 201

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


