def adv_search_serie(q, include_series_inputs, exclude_series_inputs):
    for serie in include_series_inputs:
        q = q.filter(db.Books.series.any(db.Series.id == serie))
    for serie in exclude_series_inputs:
        q = q.filter(not_(db.Books.series.any(db.Series.id == serie)))
    return q

def freqAlphabets(self, s):
    """
    :type s: str
    :rtype: str
    """
    def alpha(num):
        return chr(ord('a') + int(num)-1)

    i = len(s)-1
    result = []
    while i >= 0:
        if s[i] == '#':
            result.append(alpha(s[i-2:i]))
            i -= 3
        else:
            result.append(alpha(s[i]))
            i -= 1
    return "".join(reversed(result))



