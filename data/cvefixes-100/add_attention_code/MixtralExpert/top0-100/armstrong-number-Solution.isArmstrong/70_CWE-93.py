def _hkey(s):
    return s.title().replace('_', '-')

def isArmstrong(self, N):
    """
    :type N: int
    :rtype: bool
    """
    n_str = str(N)
    return sum(int(i)**len(n_str) for i in n_str) == N


