def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

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



