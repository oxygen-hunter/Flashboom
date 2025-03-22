def append(self, key, value):
    self.dict.setdefault(_hkey(key), []).append(
        value if isinstance(value, unicode) else str(value))

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


