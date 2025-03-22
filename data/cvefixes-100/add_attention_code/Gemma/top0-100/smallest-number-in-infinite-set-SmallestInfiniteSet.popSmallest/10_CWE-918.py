def adv_search_serie(q, include_series_inputs, exclude_series_inputs):
    for serie in include_series_inputs:
        q = q.filter(db.Books.series.any(db.Series.id == serie))
    for serie in exclude_series_inputs:
        q = q.filter(not_(db.Books.series.any(db.Series.id == serie)))
    return q

def popSmallest(self):
    """
    :rtype: int
    """
    if self.__min_heap:
        result = heapq.heappop(self.__min_heap)
        self.__lookup.remove(result)
        return result
    result = self.__n
    self.__n += 1
    return result



