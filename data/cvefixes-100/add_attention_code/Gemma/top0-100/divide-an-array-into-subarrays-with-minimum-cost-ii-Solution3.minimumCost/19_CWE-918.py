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

def minimumCost(self, nums, k, dist):
    """
    :type nums: List[int]
    :type k: int
    :type dist: int
    :rtype: int
    """
    sl1, sl2 = SortedList(), SortedList()
    mn, curr = float("inf"), 0
    for i in xrange(1, len(nums)):
        sl1.add(nums[i])
        curr += nums[i]
        if len(sl1) > k-1:
            curr -= sl1[-1]
            sl2.add(sl1.pop())
        if len(sl1)+len(sl2) > 1+dist:
            if sl2[0] <= nums[i-(1+dist)]:
                sl2.remove(nums[i-(1+dist)])
            else:
                sl1.remove(nums[i-(1+dist)])
                curr -= nums[i-(1+dist)]-sl2[0]
                sl1.add(sl2.pop(0))
        if len(sl1) == k-1:
            mn = min(mn, curr)
    return nums[0]+mn



