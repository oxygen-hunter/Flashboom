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

def numberOfNodes(self, n, queries):
    """
    :type n: int
    :type queries: List[int]
    :rtype: int
    """
    def iter_dfs():
        result = 0
        stk = [(1, 0)]
        while stk:
            u, curr = stk.pop()
            curr ^= cnt[u]%2
            result += curr
            for v in reversed(xrange(2*u, min(2*u+1, n)+1)):
                stk.append((v, curr))
        return result

    cnt = collections.Counter(queries)
    return iter_dfs()



