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

def miceAndCheese(self, reward1, reward2, k):
    """
    :type reward1: List[int]
    :type reward2: List[int]
    :type k: int
    :rtype: int
    """
    def nth_element(nums, n, left=0, compare=lambda a, b: a < b):
        def tri_partition(nums, left, right, target, compare):
            mid = left
            while mid <= right:
                if nums[mid] == target:
                    mid += 1
                elif compare(nums[mid], target):
                    nums[left], nums[mid] = nums[mid], nums[left]
                    left += 1
                    mid += 1
                else:
                    nums[mid], nums[right] = nums[right], nums[mid]
                    right -= 1
            return left, right
        
        right = len(nums)-1
        while left <= right:
            pivot_idx = random.randint(left, right)
            pivot_left, pivot_right = tri_partition(nums, left, right, nums[pivot_idx], compare)
            if pivot_left <= n <= pivot_right:
                return
            elif pivot_left > n:
                right = pivot_left-1
            else:  # pivot_right < n.
                left = pivot_right+1

    for i in xrange(len(reward1)):
        reward1[i] -= reward2[i]
    nth_element(reward1, k-1, compare=lambda a, b: a > b)
    return sum(reward2)+sum(reward1[i] for i in xrange(k))


