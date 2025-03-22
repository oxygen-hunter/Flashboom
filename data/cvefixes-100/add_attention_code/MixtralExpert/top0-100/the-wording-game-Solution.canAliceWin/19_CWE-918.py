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

def canAliceWin(self, a, b):
    """
    :type a: List[str]
    :type b: List[str]
    :rtype: bool
    """
    def is_closely_greater(a, b):
        return ord(a[0])-ord(b[0]) <= 1 and a > b

    result = True
    i, j = 0, -1
    for _ in xrange(len({w[0] for w in a})+len({w[0] for w in b})):  # each player takes turns using a word with a different first letter than the last word he played
        j = next((j for j in xrange(j+1, len(b)) if is_closely_greater(b[j], a[i])), len(b))
        if j == len(b):
            break
        while j+1 < len(b) and b[j+1][0] == b[j][0]:  # play the lexicographically greatest word with the same first letter
            j += 1
        a, b, i, j, result = b, a, j, i, not result
    return result


