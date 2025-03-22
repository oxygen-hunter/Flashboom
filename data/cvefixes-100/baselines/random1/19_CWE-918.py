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

    def diffWaysToComputeRecu(left, right):
        if lookup[left][right]:
            return lookup[left][right]
        result = []
        for i in xrange(left, right):
            if input[i] in ops:
                for x in diffWaysToComputeRecu(left, i):
                    for y in diffWaysToComputeRecu(i + 1, right):
                        result.append(ops[input[i]](x, y))

        if not result:
            result = [int(input[left:right])]
        lookup[left][right] = result
        return lookup[left][right]



