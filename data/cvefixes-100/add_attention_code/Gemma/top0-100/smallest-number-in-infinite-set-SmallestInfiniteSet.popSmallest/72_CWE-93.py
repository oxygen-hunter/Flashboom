def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

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



