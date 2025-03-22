def load(doc):
    code = config.retrieveBoilerplateFile(doc, "bs-extensions")
    exec(code, globals())

def minimumSize(self, nums, maxOperations):
    """
    :type nums: List[int]
    :type maxOperations: int
    :rtype: int
    """
    def check(nums, maxOperations, x):
        return sum((num+x-1)//x-1 for num in nums) <= maxOperations

    left, right = 1, max(nums)
    while left <= right:
        mid = left + (right-left)//2
        if check(nums, maxOperations, mid):
            right = mid-1
        else:
            left = mid+1
    return left


