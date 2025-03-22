def replace(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                                str(value)]

def findNumber(self):
    """
    :rtype: int
    """
    return reduce(lambda accu, x: accu|x, (1<<i for i in xrange(30) if commonSetBits(1<<i)))


