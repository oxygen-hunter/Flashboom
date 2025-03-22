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

def kthSmallestSubarraySum(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    def check(nums, k, x):
        cnt = curr = left = 0
        for right in xrange(len(nums)):
            curr += nums[right]
            while curr > x:
                curr -= nums[left]
                left += 1
            cnt += right-left+1
        return cnt >= k

    left, right = min(nums), sum(nums)
    while left <= right:
        mid = left + (right-left)//2
        if check(nums, k, mid):
            right = mid-1
        else:
            left = mid+1
    return left


