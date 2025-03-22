def replace(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                             str(value)]

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


