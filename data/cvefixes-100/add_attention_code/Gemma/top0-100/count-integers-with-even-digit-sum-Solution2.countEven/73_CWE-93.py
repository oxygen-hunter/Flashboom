def replace(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                                str(value)]

def countEven(self, num):
    """
    :type num: int
    :rtype: int
    """
    def parity(x):
        result = 0
        while x:
            result += x%10
            x //= 10
        return result%2

    return sum(parity(x) == 0 for x in xrange(1, num+1))



