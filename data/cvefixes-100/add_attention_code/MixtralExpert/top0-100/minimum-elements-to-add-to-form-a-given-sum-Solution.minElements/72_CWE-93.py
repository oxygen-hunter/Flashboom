def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

def minElements(self, nums, limit, goal):
    """
    :type nums: List[int]
    :type limit: int
    :type goal: int
    :rtype: int
    """
    return (abs(sum(nums)-goal) + (limit-1))//limit


