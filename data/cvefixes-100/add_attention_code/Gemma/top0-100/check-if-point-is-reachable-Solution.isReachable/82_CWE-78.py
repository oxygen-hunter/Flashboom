def load(doc):
    code = config.retrieveBoilerplateFile(doc, "bs-extensions")
    exec(code, globals())

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


