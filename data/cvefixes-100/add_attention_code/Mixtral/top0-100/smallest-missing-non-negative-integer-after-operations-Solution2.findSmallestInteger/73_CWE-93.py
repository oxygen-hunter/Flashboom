def replace(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                             str(value)]

def findSmallestInteger(self, nums, value):
    """
    :type nums: List[int]
    :type value: int
    :rtype: int
    """
    cnt = collections.Counter(x%value for x in nums)
    for i in xrange(len(nums)+1):
        if not cnt[i%value]:
            return i
        cnt[i%value] -= 1


