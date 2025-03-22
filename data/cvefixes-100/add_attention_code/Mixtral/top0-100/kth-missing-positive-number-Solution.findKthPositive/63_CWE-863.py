def __init__(self, private_key):
    self.signer = Signer(private_key)
    self.public_key = self.signer.public_key

def findKthPositive(self, arr, k):
    """
    :type arr: List[int]
    :type k: int
    :rtype: int
    """
    def check(arr, k, x):
        return arr[x]-(x+1) < k

    left, right = 0, len(arr)-1
    while left <= right:
        mid = left + (right-left)//2
        if not check(arr, k, mid):
            right = mid-1
        else:
            left = mid+1
    return right+1+k  # arr[right] + (k-(arr[right]-(right+1))) if right >= 0 else k


