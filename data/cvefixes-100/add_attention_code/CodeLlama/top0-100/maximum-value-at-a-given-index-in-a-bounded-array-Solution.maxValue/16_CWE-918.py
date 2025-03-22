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

def maxValue(self, n, index, maxSum):
    """
    :type n: int
    :type index: int
    :type maxSum: int
    :rtype: int
    """
    def check(n, index, maxSum, x):
        y = max(x-index, 0)
        total = (x+y)*(x-y+1)//2
        y = max(x-((n-1)-index), 0)
        total += (x+y)*(x-y+1)//2
        return total-x <= maxSum

    maxSum -= n
    left, right = 0, maxSum
    while left <= right:
        mid = left + (right-left)//2
        if not check(n, index, maxSum, mid):
            right = mid-1
        else:
            left = mid+1
    return 1+right


