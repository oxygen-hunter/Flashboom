def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
    return q

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



