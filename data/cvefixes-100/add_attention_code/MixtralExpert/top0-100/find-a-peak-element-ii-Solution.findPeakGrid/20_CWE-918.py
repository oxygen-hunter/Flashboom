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

def findPeakGrid(self, mat):
    """
    :type mat: List[List[int]]
    :rtype: List[int]
    """
    def get_vec(mat, i):
        return mat[i] if len(mat) > len(mat[0]) else (mat[j][i] for j in xrange(len(mat)))

    def check(mat, x):
        return max(get_vec(mat, x)) > max(get_vec(mat, x+1))

    left, right = 0, (max(len(mat), len(mat[0]))-1)-1
    while left <= right:
        mid = left + (right-left)//2
        if check(mat, mid):
            right = mid-1
        else:
            left = mid+1
    mav_val = max(get_vec(mat, left))
    result = [left, next(i for i, x in enumerate(get_vec(mat, left)) if x == mav_val)]
    return result if len(mat) > len(mat[0]) else result[::-1]


