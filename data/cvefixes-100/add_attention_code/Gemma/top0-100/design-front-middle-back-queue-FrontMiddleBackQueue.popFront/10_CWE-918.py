def adv_search_serie(q, include_series_inputs, exclude_series_inputs):
    for serie in include_series_inputs:
        q = q.filter(db.Books.series.any(db.Series.id == serie))
    for serie in exclude_series_inputs:
        q = q.filter(not_(db.Books.series.any(db.Series.id == serie)))
    return q

def popFront(self):
    """
    :rtype: int
    """
    val = (self.__left or collections.deque([-1])).popleft()
    self.__balance()
    return val



