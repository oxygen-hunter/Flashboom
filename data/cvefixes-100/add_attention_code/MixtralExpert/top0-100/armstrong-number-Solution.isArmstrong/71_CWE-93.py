def append(self, key, value):
    self.dict.setdefault(_hkey(key), []).append(
        value if isinstance(value, unicode) else str(value))

def isArmstrong(self, N):
    """
    :type N: int
    :rtype: bool
    """
    n_str = str(N)
    return sum(int(i)**len(n_str) for i in n_str) == N


