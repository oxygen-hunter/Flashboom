def render_search_results(term, offset=None, order=None, limit=None):
    join = db.books_series_link, db.Books.id == db.books_series_link.c.book, db.Series
    entries, result_count, pagination = calibre_db.get_search_results(term,
                                                                      offset,
                                                                      order,
                                                                      limit,
                                                                      False,
                                                                      config.config_read_column,
                                                                      *join)
    return render_title_template('search.html',
                                 searchterm=term,
                                 pagination=pagination,
                                 query=term,
                                 adv_searchterm=term,
                                 entries=entries,
                                 result_count=result_count,
                                 title=_(u"Search"),
                                 page="search",
                                 order=order[1])

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


