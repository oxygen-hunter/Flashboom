def adv_search_shelf(q, include_shelf_inputs, exclude_shelf_inputs):
    q = q.outerjoin(ub.BookShelf, db.Books.id == ub.BookShelf.book_id)\
        .filter(or_(ub.BookShelf.shelf == None, ub.BookShelf.shelf.notin_(exclude_shelf_inputs)))
    if len(include_shelf_inputs) > 0:
        q = q.filter(ub.BookShelf.shelf.in_(include_shelf_inputs))
    return q

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


