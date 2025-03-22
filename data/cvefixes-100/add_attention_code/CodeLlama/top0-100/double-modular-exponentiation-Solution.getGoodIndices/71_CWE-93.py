def append(self, key, value):
    self.dict.setdefault(_hkey(key), []).append(
        value if isinstance(value, unicode) else str(value))

def getGoodIndices(self, variables, target):
    """
    :type variables: List[List[int]]
    :type target: int
    :rtype: List[int]
    """
    return [i for i, (a, b, c, m) in enumerate(variables) if pow(pow(a, b, 10), c, m) == target]


