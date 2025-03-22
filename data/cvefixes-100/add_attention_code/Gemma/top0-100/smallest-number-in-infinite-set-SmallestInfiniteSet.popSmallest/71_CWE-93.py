def append(self, key, value):
    self.dict.setdefault(_hkey(key), []).append(
        value if isinstance(value, unicode) else str(value))

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



