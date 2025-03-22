def append(self, key, value):
    self.dict.setdefault(_hkey(key), []).append(
        value if isinstance(value, unicode) else str(value))

def minElements(self, nums, limit, goal):
    """
    :type nums: List[int]
    :type limit: int
    :type goal: int
    :rtype: int
    """
    return (abs(sum(nums)-goal) + (limit-1))//limit


