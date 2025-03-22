def adv_search_serie(q, include_series_inputs, exclude_series_inputs):
    for serie in include_series_inputs:
        q = q.filter(db.Books.series.any(db.Series.id == serie))
    for serie in exclude_series_inputs:
        q = q.filter(not_(db.Books.series.any(db.Series.id == serie)))
    return q

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


