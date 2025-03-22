async def send_transaction(self, account, to, selector_name, calldata, nonce=None, max_fee=0):
    return await self.send_transactions(account, [(to, selector_name, calldata)], nonce, max_fee)

def missingElement(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    def missing_count(nums, x):
        return (nums[x]-nums[0]+1)-(x-0+1)

    def check(nums, k, x):
        return k > missing_count(nums, x)

    left, right = 0, len(nums)-1
    while left <= right:  # find the largest right s.t. k > missingCount(nums, x)
        mid = left + (right-left)//2
        if not check(nums, k, mid):
            right = mid-1
        else:
            left = mid+1
    assert(check(nums, k, right))
    return nums[right] + (k-missing_count(nums, right))


