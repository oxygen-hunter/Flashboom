def append(self, key, value):
    self.dict.setdefault(_hkey(key), []).append(
        value if isinstance(value, unicode) else str(value))

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


