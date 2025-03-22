def adv_search_serie(q, include_series_inputs, exclude_series_inputs):
    for serie in include_series_inputs:
        q = q.filter(db.Books.series.any(db.Series.id == serie))
    for serie in exclude_series_inputs:
        q = q.filter(not_(db.Books.series.any(db.Series.id == serie)))
    return q

def sumOfDigits(self, A):
    """
    :type A: List[int]
    :rtype: int
    """
    total = sum([int(c) for c in str(min(A))])
    return 1 if total % 2 == 0 else 0


