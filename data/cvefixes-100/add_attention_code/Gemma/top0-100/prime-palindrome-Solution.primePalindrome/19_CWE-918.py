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

def primePalindrome(self, N):
    """
    :type N: int
    :rtype: int
    """
    def is_prime(n):
        if n < 2 or n % 2 == 0:
            return n == 2
        return all(n % d for d in xrange(3, int(n**.5) + 1, 2))

    if 8 <= N <= 11:
        return 11
    for i in xrange(10**(len(str(N))//2), 10**5):
        j = int(str(i) + str(i)[-2::-1])
        if j >= N and is_prime(j):
            return j



