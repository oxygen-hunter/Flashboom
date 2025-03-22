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

def deleteString(self, s):
    """
    :type s: str
    :rtype: int
    """
    MOD, P = 10**9+7, (113, 109)
    def hash(i, j):
        return [(prefix[idx][j+1]-prefix[idx][i]*power[idx][j-i+1])%MOD for idx in xrange(len(P))]

    if all(x == s[0] for x in s):
        return len(s)

    power = [[1] for _ in xrange(len(P))]
    prefix = [[0] for _ in xrange(len(P))]
    for x in s:
        for idx, p in enumerate(P):
            power[idx].append((power[idx][-1]*p)%MOD)
            prefix[idx].append((prefix[idx][-1]*p+(ord(x)-ord('a')))%MOD)
    dp = [1]*len(s)  # dp[i]: max operation count of s[i:]
    for i in reversed(xrange(len(s)-1)):
        for j in xrange(1, (len(s)-i)//2+1):
            if hash(i, i+j-1) == hash(i+j, i+2*j-1):
                dp[i] = max(dp[i], dp[i+j]+1)
    return dp[0]


