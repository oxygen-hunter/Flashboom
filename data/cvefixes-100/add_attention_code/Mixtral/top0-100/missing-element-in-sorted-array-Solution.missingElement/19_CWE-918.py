def download_list():
    if current_user.get_view_property('download', 'dir') == 'desc':
        order = ub.User.name.desc()
        order_no = 0
    else:
        order = ub.User.name.asc()
        order_no = 1
    if current_user.check_visibility(constants.SIDEBAR_DOWNLOAD) and current_user.role_admin():
        entries = ub.session.query(ub.User, func.count(ub.Downloads.book_id).label('count'))\
            .join(ub.Downloads).group_by(ub.Downloads.user_id).order_by(order).all()
        charlist = ub.session.query(func.upper(func.substr(ub.User.name, 1, 1)).label('char')) \
            .filter(ub.User.role.op('&')(constants.ROLE_ANONYMOUS) != constants.ROLE_ANONYMOUS) \
            .group_by(func.upper(func.substr(ub.User.name, 1, 1))).all()
        return render_title_template('list.html', entries=entries, folder='web.books_list', charlist=charlist,
                                     title=_(u"Downloads"), page="downloadlist", data="download", order=order_no)
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


