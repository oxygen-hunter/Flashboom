def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

def minTimeToVisitAllPoints(self, points):
    """
    :type points: List[List[int]]
    :rtype: int
    """
    return sum(max(abs(points[i+1][0] - points[i][0]),
                   abs(points[i+1][1] - points[i][1]))
               for i in xrange(len(points)-1))


