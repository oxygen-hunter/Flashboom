def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

def sumBase(self, n, k):
    """
    :type n: int
    :type k: int
    :rtype: int
    """
    result = 0
    while n:
        n, r = divmod(n, k)
        result += r
    return result


