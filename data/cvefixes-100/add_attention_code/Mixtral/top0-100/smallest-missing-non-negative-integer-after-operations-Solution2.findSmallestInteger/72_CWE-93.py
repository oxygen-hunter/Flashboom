def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

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


