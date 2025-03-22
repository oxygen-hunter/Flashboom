def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def minTimeToVisitAllPoints(self, points):
    """
    :type points: List[List[int]]
    :rtype: int
    """
    return sum(max(abs(points[i+1][0] - points[i][0]),
                   abs(points[i+1][1] - points[i][1]))
               for i in xrange(len(points)-1))


