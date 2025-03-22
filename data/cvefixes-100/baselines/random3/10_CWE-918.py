def adv_search_serie(q, include_series_inputs, exclude_series_inputs):
    for serie in include_series_inputs:
        q = q.filter(db.Books.series.any(db.Series.id == serie))
    for serie in exclude_series_inputs:
        q = q.filter(not_(db.Books.series.any(db.Series.id == serie)))
    return q

def subarraySum(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    result = 0
    accumulated_sum = 0
    lookup = collections.defaultdict(int)
    lookup[0] += 1
    for num in nums:
        accumulated_sum += num
        result += lookup[accumulated_sum - k]
        lookup[accumulated_sum] += 1
    return result



