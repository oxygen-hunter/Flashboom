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

def numberOfCombinations(self, num):
    """
    :type num: str
    :rtype: int
    """
    MOD = 10**9+7
    def find_longest_common_prefix(num):
        lcp = [[0]*(len(num)+1) for _ in xrange(len(num)+1)]  # lcp[i][j]: longest length of the common prefix which starts at num[i], num[j]
        for i in reversed(xrange(len(lcp)-1)):
            for j in reversed(xrange(len(lcp[0])-1)):
                if num[i] == num[j]:
                    lcp[i][j] = lcp[i+1][j+1]+1
        return lcp

    def is_less_or_equal_to_with_same_length(num, lcp, i, j, l):
        return lcp[i][j] >= l or num[i+lcp[i][j]] < num[j+lcp[i][j]]

    lcp = find_longest_common_prefix(num)
    dp = [[0]*len(num) for _ in xrange(len(num))]  # dp[i][l]: the count of numbers ending at num[i], where the length of the last number is l+1
    dp[0][0] = int(num[0] != '0')
    for i in xrange(1, len(num)):
        dp[i][i] = dp[i-1][i-1]
        if num[i] == '0':
            continue
        accu = 0
        for l in xrange(len(num)-i+1):
            ni = i+l-1
            dp[ni][l-1] = accu  # accumulated count where the length of the second to last number ending at num[i-1] is shorter than the length of the last number ending at num[i+l-1]
            if i-l < 0:
                continue
            if num[i-l] != '0' and is_less_or_equal_to_with_same_length(num, lcp, i-l, i, l):
                dp[ni][l-1] = (dp[ni][l-1] + dp[i-1][l-1]) % MOD
            accu = (accu + dp[i-1][l-1]) % MOD
    return reduce(lambda total, x: (total+x)%MOD, dp[-1], 0)


