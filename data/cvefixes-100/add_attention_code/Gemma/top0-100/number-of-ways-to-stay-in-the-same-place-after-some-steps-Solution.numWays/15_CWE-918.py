def category_list():
    if current_user.check_visibility(constants.SIDEBAR_CATEGORY):
        if current_user.get_view_property('category', 'dir') == 'desc':
            order = db.Tags.name.desc()
            order_no = 0
        else:
            order = db.Tags.name.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Tags, func.count('books_tags_link.book').label('count')) \
            .join(db.books_tags_link).join(db.Books).order_by(order).filter(calibre_db.common_filters()) \
            .group_by(text('books_tags_link.tag')).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Tags.name, 1, 1)).label('char')) \
            .join(db.books_tags_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Tags.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Categories"), page="catlist", data="category", order=order_no)
    else:
        abort(404)

def numWays(self, steps, arrLen):
    """
    :type steps: int
    :type arrLen: int
    :rtype: int
    """
    MOD = int(1e9+7)
    l = min(1+steps//2, arrLen)
    dp = [0]*(l+2)
    dp[1] = 1
    while steps > 0:
        steps -= 1
        new_dp = [0]*(l+2)
        for i in xrange(1, l+1):
            new_dp[i] = (dp[i] + dp[i-1] + dp[i+1]) % MOD
        dp = new_dp
    return dp[1]


