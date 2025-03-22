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

def minimumCost(self, nums, k, dist):
    """
    :type nums: List[int]
    :type k: int
    :type dist: int
    :rtype: int
    """
    sl1, sl2 = SortedList(), SortedList()
    mn, curr = float("inf"), 0
    for i in xrange(1, len(nums)):
        sl1.add(nums[i])
        curr += nums[i]
        if len(sl1) > k-1:
            curr -= sl1[-1]
            sl2.add(sl1.pop())
        if len(sl1)+len(sl2) > 1+dist:
            if sl2[0] <= nums[i-(1+dist)]:
                sl2.remove(nums[i-(1+dist)])
            else:
                sl1.remove(nums[i-(1+dist)])
                curr -= nums[i-(1+dist)]-sl2[0]
                sl1.add(sl2.pop(0))
        if len(sl1) == k-1:
            mn = min(mn, curr)
    return nums[0]+mn



