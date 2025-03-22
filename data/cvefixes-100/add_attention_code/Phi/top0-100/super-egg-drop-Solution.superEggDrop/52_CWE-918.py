def render_read_books(page, are_read, as_xml=False, order=None):
    sort_param = order[0] if order else []
    if not config.config_read_column:
        if are_read:
            db_filter = and_(ub.ReadBook.user_id == int(current_user.id),
                             ub.ReadBook.read_status == ub.ReadBook.STATUS_FINISHED)
        else:
            db_filter = coalesce(ub.ReadBook.read_status, 0) != ub.ReadBook.STATUS_FINISHED
        entries, random, pagination = calibre_db.fill_indexpage(page, 0,
                                                                db.Books,
                                                                db_filter,
                                                                sort_param,
                                                                False, 0,
                                                                db.books_series_link,
                                                                db.Books.id == db.books_series_link.c.book,
                                                                db.Series,
                                                                ub.ReadBook, db.Books.id == ub.ReadBook.book_id)
    else:
        try:
            if are_read:
                db_filter = db.cc_classes[config.config_read_column].value == True
            else:
                db_filter = coalesce(db.cc_classes[config.config_read_column].value, False) != True
            entries, random, pagination = calibre_db.fill_indexpage(page, 0,
                                                                    db.Books,
                                                                    db_filter,
                                                                    sort_param,
                                                                    False, 0,
                                                                    db.books_series_link,
                                                                    db.Books.id == db.books_series_link.c.book,
                                                                    db.Series,
                                                                    db.cc_classes[config.config_read_column])
        except (KeyError, AttributeError):
            log.error("Custom Column No.%d is not existing in calibre database", config.config_read_column)
            if not as_xml:
                flash(_("Custom Column No.%(column)d is not existing in calibre database",
                        column=config.config_read_column),
                      category="error")
                return redirect(url_for("web.index"))
            return [] # ToDo: Handle error Case for opds

    if as_xml:
        return entries, pagination
    else:
        if are_read:
            name = _(u'Read Books') + ' (' + str(pagination.total_count) + ')'
            pagename = "read"
        else:
            name = _(u'Unread Books') + ' (' + str(pagination.total_count) + ')'
            pagename = "unread"
        return render_title_template('index.html', random=random, entries=entries, pagination=pagination,
                                     title=name, page=pagename, order=order[1])

def superEggDrop(self, K, N):
    """
    :type K: int
    :type N: int
    :rtype: int
    """
    def check(n, K, N):
        # let f(n, K) be the max number of floors could be solved by n moves and K eggs,
        # we want to do binary search to find min of n, s.t. f(n, K) >= N,
        # if we use one move to drop egg with X floors
        # 1. if it breaks, we can search new X in the range [X+1, X+f(n-1, K-1)]
        # 2. if it doesn't break, we can search new X in the range [X-f(n-1, K), X-1]
        # => f(n, K) = (X+f(n-1, K-1))-(X-f(n-1, K))+1 = f(n-1, K-1)+f(n-1, K)+1
        # => (1) f(n, K)   = f(n-1, K)  +1+f(n-1, K-1)
        #    (2) f(n, K-1) = f(n-1, K-1)+1+f(n-1, K-2)
        # let g(n, K) = f(n, K)-f(n, K-1), and we subtract (1) by (2)
        # => g(n, K) = g(n-1, K)+g(n-1, K-1), obviously, it is binomial coefficient
        # => C(n, K) = g(n, K) = f(n, K)-f(n, K-1),
        #    which also implies if we have one more egg with n moves and x-1 egges, we can have more C(n, x) floors solvable
        # => f(n, K) = C(n, K)+f(n, K-1) = C(n, K) + C(n, K-1) + ... + C(n, 1) + f(n, 0) = sum(C(n, k) for k in [1, K])
        # => all we have to do is to check sum(C(n, k) for k in [1, K]) >= N,
        #    if true, there must exist a 1-to-1 mapping from each F in [1, N] to each sucess and failure sequence of every C(n, k) combinations for k in [1, K]
        total, c = 0, 1
        for k in xrange(1, K+1):
            c *= n-k+1
            c //= k
            total += c
            if total >= N:
                return True
        return False

    left, right = 1, N
    while left <= right:
        mid = left + (right-left)//2
        if check(mid, K, N):
            right = mid-1
        else:
            left = mid+1
    return left



