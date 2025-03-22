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

def findIndices(self, nums, indexDifference, valueDifference):
    """
    :type nums: List[int]
    :type indexDifference: int
    :type valueDifference: int
    :rtype: List[int]
    """
    mx_i = mn_i = 0
    for i in xrange(len(nums)-indexDifference):
        if nums[i] > nums[mx_i]:
            mx_i = i
        elif nums[i] < nums[mn_i]:
            mn_i = i
        # we don't need to add abs for the difference since
        # - if nums[mx_i]-nums[i+indexDifference] < 0, then checking nums[i+indexDifference]-nums[mn_i] >= -(nums[mx_i]-nums[i+indexDifference]) > 0 can cover the case
        # - if nums[i+indexDifference]-nums[mn_i] < 0, then checking nums[mx_i]-nums[i+indexDifference] >= -(nums[i+indexDifference]-nums[mn_i]) > 0 can cover the case
        if nums[mx_i]-nums[i+indexDifference] >= valueDifference:
            return [mx_i, i+indexDifference]
        if nums[i+indexDifference]-nums[mn_i] >= valueDifference:
            return [mn_i, i+indexDifference]
    return [-1]*2


