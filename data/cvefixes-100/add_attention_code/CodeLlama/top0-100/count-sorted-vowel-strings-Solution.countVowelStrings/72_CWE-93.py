def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

def countVowelStrings(self, n):
    """
    :type n: int
    :rtype: int
    """
    def nCr(n, r):  # Time: O(n), Space: O(1)
        if n-r < r:
            return nCr(n, n-r)
        c = 1
        for k in xrange(1, r+1):
            c *= n-k+1
            c //= k
        return c

    return nCr(n+4, 4)  # H(5, n) = C(n+5-1, n) = C(n+4, 4)


