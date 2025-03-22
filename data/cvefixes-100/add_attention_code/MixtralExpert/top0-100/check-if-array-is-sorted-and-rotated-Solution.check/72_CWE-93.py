def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

def check(self, nums):
    """
    :type nums: List[int]
    :rtype: bool
    """
    count = 0
    for i in xrange(len(nums)):
        if nums[i] > nums[(i+1)%len(nums)]:
            count += 1
            if count > 1:
                return False
    return True


