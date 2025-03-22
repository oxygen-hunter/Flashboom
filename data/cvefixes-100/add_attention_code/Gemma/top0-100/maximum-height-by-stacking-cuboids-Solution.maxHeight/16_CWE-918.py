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

def maxHeight(self, cuboids):
    """
    :type cuboids: List[List[int]]
    :rtype: int
    """
    for cuboid in cuboids:
        cuboid.sort()
    cuboids.append([0, 0, 0])
    cuboids.sort()
    dp = [0]*len(cuboids)
    for i in xrange(1, len(cuboids)):
        for j in xrange(i):
            if all(cuboids[j][k] <= cuboids[i][k] for k in xrange(3)):
                dp[i] = max(dp[i], dp[j]+cuboids[i][2])
    return max(dp)


