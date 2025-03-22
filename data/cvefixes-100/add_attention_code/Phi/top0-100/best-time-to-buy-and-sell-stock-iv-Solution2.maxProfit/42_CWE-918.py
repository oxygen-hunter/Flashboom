def render_archived_books(page, sort_param):
    order = sort_param[0] or []
    archived_books = (
        ub.session.query(ub.ArchivedBook)
        .filter(ub.ArchivedBook.user_id == int(current_user.id))
        .filter(ub.ArchivedBook.is_archived == True)
        .all()
    )
    archived_book_ids = [archived_book.book_id for archived_book in archived_books]

    archived_filter = db.Books.id.in_(archived_book_ids)

    entries, random, pagination = calibre_db.fill_indexpage_with_archived_books(page, db.Books,
                                                                                0,
                                                                                archived_filter,
                                                                                order,
                                                                                True,
                                                                                False, 0)

    name = _(u'Archived Books') + ' (' + str(len(archived_book_ids)) + ')'
    pagename = "archived"
    return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                 title=name, page=pagename, order=sort_param[1])

def maxProfit(self, k, prices):
    """
    :type k: int
    :type prices: List[int]
    :rtype: int
    """
    def maxAtMostNPairsProfit(sprices):
        profit = 0
        for i in xrange(len(prices) - 1):
            profit += max(0, prices[i + 1] - prices[i])
        return profit

    def maxAtMostKPairsProfit(prices, k):
        max_buy = [float("-inf") for _ in xrange(k + 1)]
        max_sell = [0 for _ in xrange(k + 1)]
        for i in xrange(len(prices)):
            for j in xrange(1, k + 1):
                max_buy[j] = max(max_buy[j], max_sell[j-1] - prices[i])
                max_sell[j] = max(max_sell[j], max_buy[j] + prices[i])
        return max_sell[k]

    if k >= len(prices) // 2:
        return maxAtMostNPairsProfit(prices)

    return maxAtMostKPairsProfit(prices, k)


