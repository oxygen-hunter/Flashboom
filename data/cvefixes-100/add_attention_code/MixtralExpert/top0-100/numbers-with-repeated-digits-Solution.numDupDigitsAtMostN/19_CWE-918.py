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

def numDupDigitsAtMostN(self, N):
    """
    :type N: int
    :rtype: int
    """
    def P(m, n):
        result = 1
        for _ in xrange(n):
            result *= m
            m -= 1
        return result

    digits = map(int, str(N+1))
    result = 0

    # Given 321
    #
    # 1. count numbers without repeated digits:
    # - X
    # - XX
    for i in xrange(1, len(digits)):
        result += P(9, 1)*P(9, i-1)
    
    # 2. count numbers without repeated digits:
    # - 1XX ~ 3XX
    # - 30X ~ 32X
    # - 320 ~ 321
    prefix_set = set()
    for i, x in enumerate(digits):
        for y in xrange(1 if i == 0 else 0, x):
            if y in prefix_set:
                continue
            result += P(9-i, len(digits)-i-1)
        if x in prefix_set:
            break
        prefix_set.add(x)
    return N-result


