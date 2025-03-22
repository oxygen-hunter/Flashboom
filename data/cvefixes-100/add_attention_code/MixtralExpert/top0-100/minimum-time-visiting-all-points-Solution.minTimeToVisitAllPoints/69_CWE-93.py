def __setitem__(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                                str(value)]

def minTimeToVisitAllPoints(self, points):
    """
    :type points: List[List[int]]
    :rtype: int
    """
    return sum(max(abs(points[i+1][0] - points[i][0]),
                   abs(points[i+1][1] - points[i][1]))
               for i in xrange(len(points)-1))


