def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def isReachable(self, targetX, targetY):
    """
    :type targetX: int
    :type targetY: int
    :rtype: bool
    """
    def gcd(a, b):
        while b:
            a, b = b, a%b
        return a

    g = gcd(targetX, targetY)
    return g == (g&~(g-1))  # co-prime other than factor 2


