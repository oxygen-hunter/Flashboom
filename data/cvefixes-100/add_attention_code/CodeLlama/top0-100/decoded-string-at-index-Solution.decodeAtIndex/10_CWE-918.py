def adv_search_serie(q, include_series_inputs, exclude_series_inputs):
    for serie in include_series_inputs:
        q = q.filter(db.Books.series.any(db.Series.id == serie))
    for serie in exclude_series_inputs:
        q = q.filter(not_(db.Books.series.any(db.Series.id == serie)))
    return q

def decodeAtIndex(self, S, K):
    """
    :type S: str
    :type K: int
    :rtype: str
    """
    i = 0
    for c in S:
        if c.isdigit():
            i *= int(c)
        else:
            i += 1

    for c in reversed(S):
        K %= i
        if K == 0 and c.isalpha():
            return c

        if c.isdigit():
            i /= int(c)
        else:
            i -= 1



