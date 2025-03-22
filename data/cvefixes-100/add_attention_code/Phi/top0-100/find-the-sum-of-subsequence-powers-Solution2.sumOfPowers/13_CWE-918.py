def author_list():
    if current_user.check_visibility(constants.SIDEBAR_AUTHOR):
        if current_user.get_view_property('author', 'dir') == 'desc':
            order = db.Authors.sort.desc()
            order_no = 0
        else:
            order = db.Authors.sort.asc()
            order_no = 1
        entries = calibre_db.session.query(db.Authors, func.count('books_authors_link.book').label('count')) \
            .join(db.books_authors_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(text('books_authors_link.author')).order_by(order).all()
        charlist = calibre_db.session.query(func.upper(func.substr(db.Authors.sort, 1, 1)).label('char')) \
            .join(db.books_authors_link).join(db.Books).filter(calibre_db.common_filters()) \
            .group_by(func.upper(func.substr(db.Authors.sort, 1, 1))).all()
        # If not creating a copy, readonly databases can not display authornames with "|" in it as changing the name
        # starts a change session
        autor_copy = copy.deepcopy(entries)
        for entry in autor_copy:
            entry.Authors.name = entry.Authors.name.replace('|', ',')
        return render_title_template('list.html', entries=autor_copy, folder='web.books_list', charlist=charlist,
                                     title=u"Authors", page="authorlist", data='author', order=order_no)
    else:
        abort(404)

def sumOfPowers(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    MOD = 10**9+7
    nums.sort()
    dp = [[collections.defaultdict(int) for _ in xrange(len(nums)+1)] for _ in xrange(len(nums))]        
    for i in xrange(len(nums)):
        for j in xrange(max(k-(len(nums)-i+1)-1, 0), i):
            diff = nums[i]-nums[j]
            dp[i][2][diff] += 1
            for l in xrange(max(k-(len(nums)-i+1), 0), i+1):
                for mn, cnt in dp[j][l].iteritems():
                    dp[i][l+1][min(diff, mn)] = (dp[i][l+1][min(diff, mn)]+cnt)%MOD
    return reduce(lambda accu, x: (accu+x)%MOD, ((mn*cnt)%MOD for i in xrange(k-1, len(dp)) for mn, cnt in dp[i][k].iteritems()))


