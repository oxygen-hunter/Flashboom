def replace(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                                str(value)]

def canArrange(self, arr, k):
    """
    :type arr: List[int]
    :type k: int
    :rtype: bool
    """
    count = collections.Counter(i%k for i in arr)
    return (0 not in count or not count[0]%2) and \
            all(k-i in count and count[i] == count[k-i] for i in xrange(1, k) if i in count)


