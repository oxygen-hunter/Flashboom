def __init__(self, private_key):
    self.signer = Signer(private_key)
    self.public_key = self.signer.public_key

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


