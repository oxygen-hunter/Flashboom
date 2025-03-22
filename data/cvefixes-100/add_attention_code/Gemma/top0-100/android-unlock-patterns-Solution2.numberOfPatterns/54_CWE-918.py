def render_search_results(term, offset=None, order=None, limit=None):
    join = db.books_series_link, db.Books.id == db.books_series_link.c.book, db.Series
    entries, result_count, pagination = calibre_db.get_search_results(term,
                                                                      offset,
                                                                      order,
                                                                      limit,
                                                                      False,
                                                                      config.config_read_column,
                                                                      *join)
    return render_title_template('search.html',
                                 searchterm=term,
                                 pagination=pagination,
                                 query=term,
                                 adv_searchterm=term,
                                 entries=entries,
                                 result_count=result_count,
                                 title=_(u"Search"),
                                 page="search",
                                 order=order[1])

def numberOfPatterns(self, m, n):
    """
    :type m: int
    :type n: int
    :rtype: int
    """
    def merge(used, i):
        return used | (1 << i)

    def number_of_keys(i):
        number = 0
        while i > 0:
            i &= i - 1
            number += 1
        return number

    def exclude(used, i):
        return used & ~(1 << i)

    def contain(used, i):
        return bool(used & (1 << i))

    def convert(i, j):
        return 3 * i + j

    # dp[i][j]: i is the set of the numbers in binary representation,
    #            d[i][j] is the number of ways ending with the number j.
    dp = [[0] * 9 for _ in xrange(1 << 9)]
    for i in xrange(9):
        dp[merge(0, i)][i] = 1

    res = 0
    for used in xrange(len(dp)):
        number = number_of_keys(used)
        if number > n:
            continue

        for i in xrange(9):
            if not contain(used, i):
                continue

            x1, y1 = divmod(i, 3)
            for j in xrange(9):
                if i == j or not contain(used, j):
                    continue

                x2, y2 = divmod(j, 3)
                if ((x1 == x2 and abs(y1 - y2) == 2) or
                    (y1 == y2 and abs(x1 - x2) == 2) or
                    (abs(x1 - x2) == 2 and abs(y1 - y2) == 2)) and \
                   not contain(used,
                               convert((x1 + x2) // 2, (y1 + y2) // 2)):
                        continue

                dp[used][i] += dp[exclude(used, i)][j]

            if m <= number <= n:
                res += dp[used][i]

    return res



