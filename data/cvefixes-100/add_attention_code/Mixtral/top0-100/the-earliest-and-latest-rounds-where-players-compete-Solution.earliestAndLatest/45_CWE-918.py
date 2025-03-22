def render_downloaded_books(page, order, user_id):
    if current_user.role_admin():
        user_id = int(user_id)
    else:
        user_id = current_user.id
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD):
        if current_user.show_detail_random():
            random = calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                .order_by(func.random()).limit(config.config_random_books)
        else:
            random = false()

        entries, __, pagination = calibre_db.fill_indexpage(page,
                                                            0,
                                                            db.Books,
                                                            ub.Downloads.user_id == user_id,
                                                            order[0],
                                                            False, 0,
                                                            db.books_series_link,
                                                            db.Books.id == db.books_series_link.c.book,
                                                            db.Series,
                                                            ub.Downloads, db.Books.id == ub.Downloads.book_id)
        for book in entries:
            if not calibre_db.session.query(db.Books).filter(calibre_db.common_filters()) \
                             .filter(db.Books.id == book.id).first():
                ub.delete_download(book.id)
        user = ub.session.query(ub.User).filter(ub.User.id == user_id).first()
        return render_title_template('index.html',
                                     random=random,
                                     entries=entries,
                                     pagination=pagination,
                                     id=user_id,
                                     title=_(u"Downloaded books by %(user)s",user=user.name),
                                     page="download",
                                     order=order[1])
    else:
        abort(404)

def earliestAndLatest(self, n, firstPlayer, secondPlayer):
    """
    :type n: int
    :type firstPlayer: int
    :type secondPlayer: int
    :rtype: List[int]
    """
    def memoization(t, l, r, lookup):
        # t: total number of players,
        # l: number of players left to the nearest top2 player,
        # r: number of players right to the nearest top2 player
        if (t, l, r) not in lookup:
            if l == r:
                return (1, 1)
            if l > r:  # make sure l <= r
                l, r, = r, l
            result = [float("inf"), 0]
            for i in xrange(l+1):
                l_win_cnt, l_lose_cnt, nt, pair_cnt = i+1, l-i, (t+1)//2, t//2
                min_j = max(l_lose_cnt, r-(pair_cnt-l_lose_cnt))  # j >= l_lose_cnt and j >= r-(pair_cnt-l_lose_cnt)
                max_j = min(r-l_win_cnt, (nt-l_win_cnt)-1)  # j <= r-l_win_cnt and j <= (nt-l_win_cnt)-1
                for j in xrange(min_j, max_j+1):
                    tmp = memoization(nt, i, j, lookup)
                    result = min(result[0], tmp[0]+1), max(result[1], tmp[1]+1)
            lookup[t, l, r] = result
        return lookup[t, l, r]
    
    return memoization(n, firstPlayer-1, n-secondPlayer, {})


