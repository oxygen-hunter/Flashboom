def adv_search_serie(q, include_series_inputs, exclude_series_inputs):
    for serie in include_series_inputs:
        q = q.filter(db.Books.series.any(db.Series.id == serie))
    for serie in exclude_series_inputs:
        q = q.filter(not_(db.Books.series.any(db.Series.id == serie)))
    return q

def getMinDistance(self, nums, target, start):
    """
    :type nums: List[int]
    :type target: int
    :type start: int
    :rtype: int
    """
    for i in xrange(len(nums)):
        if (start-i >= 0 and nums[start-i] == target) or \
           (start+i < len(nums) and nums[start+i] == target):
            break
    return i


