async def send_transaction(self, account, to, selector_name, calldata, nonce=None, max_fee=0):
    return await self.send_transactions(account, [(to, selector_name, calldata)], nonce, max_fee)

def maxPossibleScore(self, start, d):
    """
    :type start: List[int]
    :type d: int
    :rtype: int
    """
    def binary_search_right(left, right, check):
        while left <= right:
            mid = left+(right-left)//2
            if not check(mid):
                right = mid-1
            else:
                left = mid+1
        return right

    def check(x):
        curr = float("-inf")
        for i in start:
            curr = max(curr+x, i)
            if curr > i+d:
                return False
        return True

    start.sort()
    return binary_search_right(1, start[-1]+d-start[0], check)


