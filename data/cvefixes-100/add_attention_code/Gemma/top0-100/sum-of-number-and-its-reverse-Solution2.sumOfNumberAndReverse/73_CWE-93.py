def replace(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                                str(value)]

def sumOfNumberAndReverse(self, num):
    """
    :type num: int
    :rtype: bool
    """
    def reverse(n):
        result = 0
        while n:
            result = result*10 + n%10
            n //= 10            
        return result

    return any(x+reverse(x) == num for x in xrange(num//2, num+1))



