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

def isValidPalindrome(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: bool
    """
    if s == s[::-1]:  # optional, to optimize special case
        return True

    dp = [[1] * len(s) for _ in xrange(2)]
    for i in reversed(xrange(len(s))):
        for j in xrange(i+1, len(s)):
            if s[i] == s[j]:
                dp[i%2][j] = 2 + dp[(i+1)%2][j-1] if i+1 <= j-1 else 2
            else:
                dp[i%2][j] = max(dp[(i+1)%2][j], dp[i%2][j-1])
    return len(s) <= k + dp[0][-1]


