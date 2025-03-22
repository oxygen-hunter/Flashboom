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

def query(self, L, R):  # Time: O(logN), Space: O(N)
    def push(x):
        n = 2**self.H
        while n != 1:
            y = x // n
            if self.lazy[y] is not None:
                self.__apply(y*2, self.lazy[y])
                self.__apply(y*2 + 1, self.lazy[y])
                self.lazy[y] = None
            n //= 2

    result = None
    if L > R:
        return result

    L += self.N
    R += self.N
    push(L)
    push(R)
    while L <= R:
        if L & 1:  # is right child
            result = self.query_fn(result, self.tree[L])
            L += 1
        if R & 1 == 0:  # is left child
            result = self.query_fn(result, self.tree[R])
            R -= 1
        L //= 2
        R //= 2
    return result



