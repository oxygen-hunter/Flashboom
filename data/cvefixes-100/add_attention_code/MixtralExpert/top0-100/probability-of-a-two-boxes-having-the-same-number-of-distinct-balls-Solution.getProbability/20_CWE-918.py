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

def getProbability(self, balls):
    """
    :type balls: List[int]
    :rtype: float
    """
    def nCrs(n):  # Time: O(n), Space: O(1)
        c = 1
        for k in xrange(n+1):
            yield c
            c *= n-(k+1)+1
            c //= k+1
    
    def nCr(n, r):  # Time: O(n), Space: O(1)
        if n-r < r:
            return nCr(n, n-r)
        c = 1
        for k in xrange(1, r+1):
            c *= n-k+1
            c //= k
        return c
    
    dp = collections.defaultdict(int)
    dp[0, 0] = 1  # dp[i, j] is the number of ways with number difference i and color difference j
    for n in balls:  # O(k) times
        new_dp = collections.defaultdict(int)
        for (ndiff, cdiff), count in dp.iteritems():  # O(k^2 * n) times
            for k, new_count in enumerate(nCrs(n)):  # O(n) times
                new_ndiff = ndiff+(k-(n-k))
                new_cdiff = cdiff-1 if k == 0 else (cdiff+1 if k == n else cdiff)
                new_dp[new_ndiff, new_cdiff] += count*new_count
        dp = new_dp
    total = sum(balls)
    return float(dp[0, 0])/nCr(total, total//2)


