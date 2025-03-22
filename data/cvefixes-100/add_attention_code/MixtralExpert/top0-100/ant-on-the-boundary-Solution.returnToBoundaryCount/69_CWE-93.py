def __setitem__(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                                str(value)]

def returnToBoundaryCount(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    result = curr = 0
    for x in nums:
        curr += x
        if curr == 0:
            result += 1
    return result


