def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

def getGoodIndices(self, variables, target):
    """
    :type variables: List[List[int]]
    :type target: int
    :rtype: List[int]
    """
    return [i for i, (a, b, c, m) in enumerate(variables) if pow(pow(a, b, 10), c, m) == target]


