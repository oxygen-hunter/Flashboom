def adv_search_serie(q, include_series_inputs, exclude_series_inputs):
    for serie in include_series_inputs:
        q = q.filter(db.Books.series.any(db.Series.id == serie))
    for serie in exclude_series_inputs:
        q = q.filter(not_(db.Books.series.any(db.Series.id == serie)))
    return q

def maximumSum(self, arr):
    """
    :type arr: List[int]
    :rtype: int
    """
    result, prev, curr = float("-inf"), float("-inf"), float("-inf")
    for x in arr:
        curr = max(prev, curr+x, x)
        result = max(result, curr)
        prev = max(prev+x, x)
    return result


