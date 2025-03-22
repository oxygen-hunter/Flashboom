def adv_search_serie(q, include_series_inputs, exclude_series_inputs):
    for serie in include_series_inputs:
        q = q.filter(db.Books.series.any(db.Series.id == serie))
    for serie in exclude_series_inputs:
        q = q.filter(not_(db.Books.series.any(db.Series.id == serie)))
    return q

def minimumOperations(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    even_top = collections.Counter(nums[i] for i in xrange(0, len(nums), 2)).most_common(2)  # Time: O(nlogk)
    odd_top = collections.Counter(nums[i] for i in xrange(1, len(nums), 2)).most_common(2)  # Time: O(nlogk)
    if not odd_top or even_top[0][0] != odd_top[0][0]:
        return len(nums)-even_top[0][1]-(odd_top[0][1] if odd_top else 0)
    return min(len(nums)-even_top[0][1]-(odd_top[1][1] if len(odd_top) == 2 else 0),
               len(nums)-odd_top[0][1]-(even_top[1][1] if len(even_top) == 2 else 0))


