def __init__(self, private_key):
    self.signer = Signer(private_key)
    self.public_key = self.signer.public_key

def maxValue(self, n, index, maxSum):
    """
    :type n: int
    :type index: int
    :type maxSum: int
    :rtype: int
    """
    def check(n, index, maxSum, x):
        y = max(x-index, 0)
        total = (x+y)*(x-y+1)//2
        y = max(x-((n-1)-index), 0)
        total += (x+y)*(x-y+1)//2
        return total-x <= maxSum

    maxSum -= n
    left, right = 0, maxSum
    while left <= right:
        mid = left + (right-left)//2
        if not check(n, index, maxSum, mid):
            right = mid-1
        else:
            left = mid+1
    return 1+right


