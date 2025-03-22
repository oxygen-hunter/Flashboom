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

def isMajorityElement(self, nums, target):
    """
    :type nums: List[int]
    :type target: int
    :rtype: bool
    """
    if len(nums) % 2:
        if nums[len(nums)//2] != target:
            return False
    else:
        if not (nums[len(nums)//2-1] == nums[len(nums)//2] == target):
            return False

    left = bisect.bisect_left(nums, target)
    right= bisect.bisect_right(nums, target)
    return (right-left)*2 > len(nums)


