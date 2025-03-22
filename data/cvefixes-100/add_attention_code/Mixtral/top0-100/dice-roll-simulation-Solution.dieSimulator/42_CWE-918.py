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

def dieSimulator(self, n, rollMax):
    """
    :type n: int
    :type rollMax: List[int]
    :rtype: int
    """
    MOD = 10**9+7
    def sum_mod(array):
        return reduce(lambda x, y: (x+y)%MOD, array)

    dp = [[1] + [0]*(rollMax[i]-1) for i in xrange(6)]  # 0-indexed
    for _ in xrange(n-1):
        new_dp = [[0]*rollMax[i] for i in xrange(6)]
        for i in xrange(6):
            for k in xrange(rollMax[i]):
                for j in xrange(6):
                    if i == j:
                        if k < rollMax[i]-1:  # 0-indexed
                            new_dp[j][k+1] = (new_dp[j][k+1]+dp[i][k])%MOD
                    else:
                        new_dp[j][0] = (new_dp[j][0]+dp[i][k])%MOD
        dp = new_dp
    return sum_mod(sum_mod(row) for row in dp)


