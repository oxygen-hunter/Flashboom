def __init__(self, private_key):
    self.signer = Signer(private_key)
    self.public_key = self.signer.public_key

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


