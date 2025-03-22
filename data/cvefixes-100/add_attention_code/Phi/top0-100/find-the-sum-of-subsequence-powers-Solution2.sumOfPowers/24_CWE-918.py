def language_overview():
    if current_user.check_visibility(constants.SIDEBAR_LANGUAGE) and current_user.filter_language() == u"all":
        order_no = 0 if current_user.get_view_property('language', 'dir') == 'desc' else 1
        charlist = list()
        languages = calibre_db.speaking_language(reverse_order=not order_no, with_count=True)
        for lang in languages:
            upper_lang = lang[0].name[0].upper()
            if upper_lang not in charlist:
                charlist.append(upper_lang)
        return render_title_template('languages.html', languages=languages,
                                     charlist=charlist, title=_(u"Languages"), page="langlist",
                                     data="language", order=order_no)
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


