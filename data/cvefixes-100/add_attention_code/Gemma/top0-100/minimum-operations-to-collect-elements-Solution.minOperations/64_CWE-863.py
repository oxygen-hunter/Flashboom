async def send_transaction(self, account, to, selector_name, calldata, nonce=None, max_fee=0):
    return await self.send_transactions(account, [(to, selector_name, calldata)], nonce, max_fee)

def minOperations(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    lookup = [False]*k
    for i in reversed(xrange(len(nums))):
        if nums[i] > len(lookup) or lookup[nums[i]-1]:
            continue
        lookup[nums[i]-1] = True
        k -= 1
        if not k:
            break
    return len(nums)-i


