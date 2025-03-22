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

def minimumSwap(self, s1, s2):
    """
    :type s1: str
    :type s2: str
    :rtype: int
    """
    x1, y1 = 0, 0
    for i in xrange(len(s1)):
        if s1[i] == s2[i]:
            continue
        x1 += int(s1[i] == 'x')
        y1 += int(s1[i] == 'y')
    if x1%2 !=  y1%2:  # impossible
        return -1
    # case1: per xx or yy needs one swap, (x1//2 + y1//2) 
    # case2: per xy or yx needs two swaps, (x1%2 + y1%2)
    return (x1//2 + y1//2) + (x1%2 + y1%2)


