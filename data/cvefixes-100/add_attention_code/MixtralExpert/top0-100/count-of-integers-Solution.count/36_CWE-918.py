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

def count(self, num1, num2, min_sum, max_sum):
    """
    :type num1: str
    :type num2: str
    :type min_sum: int
    :type max_sum: int
    :rtype: int
    """
    MOD = 10**9+7
    def f(x):
        dp = [[0]*(max_sum+1) for _ in xrange(2)]
        dp[0][0] = dp[1][0] = 1
        for i in reversed(xrange(len(x))):
            new_dp = [[0]*(max_sum+1) for _ in xrange(2)]
            for t in xrange(2):
                for total in xrange(max_sum+1):
                    for d in xrange(min((int(x[i]) if t else 9), total)+1):
                        new_dp[t][total] = (new_dp[t][total]+dp[int(t and d == int(x[i]))][total-d])%MOD
            dp = new_dp
        return reduce(lambda x, y: (x+y)%MOD, (dp[1][total] for total in xrange(min_sum, max_sum+1)))

    return (f(num2)-f(str(int(num1)-1)))%MOD


