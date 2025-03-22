def __init__(self, private_key):
    self.signer = Signer(private_key)
    self.public_key = self.signer.public_key

def minElements(self, nums, limit, goal):
    """
    :type nums: List[int]
    :type limit: int
    :type goal: int
    :rtype: int
    """
    return (abs(sum(nums)-goal) + (limit-1))//limit


