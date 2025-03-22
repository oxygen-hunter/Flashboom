async def send_transaction(self, account, to, selector_name, calldata, nonce=None, max_fee=0):
    return await self.send_transactions(account, [(to, selector_name, calldata)], nonce, max_fee)

def maxLength(self, ribbons, k):
    """
    :type ribbons: List[int]
    :type k: int
    :rtype: int
    """
    def check(ribbons, k, s):
        return reduce(lambda total,x: total+x//s, ribbons, 0) >= k

    left, right = 1, sum(ribbons)//k
    while left <= right:
        mid = left + (right-left)//2
        if not check(ribbons, k, mid):
            right = mid-1
        else:
            left = mid+1
    return right


