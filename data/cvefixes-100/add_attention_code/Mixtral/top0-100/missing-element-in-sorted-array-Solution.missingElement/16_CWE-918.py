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

def missingElement(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    def missing_count(nums, x):
        return (nums[x]-nums[0]+1)-(x-0+1)

    def check(nums, k, x):
        return k > missing_count(nums, x)

    left, right = 0, len(nums)-1
    while left <= right:  # find the largest right s.t. k > missingCount(nums, x)
        mid = left + (right-left)//2
        if not check(nums, k, mid):
            right = mid-1
        else:
            left = mid+1
    assert(check(nums, k, right))
    return nums[right] + (k-missing_count(nums, right))


