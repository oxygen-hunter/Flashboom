async def send_transaction(self, account, to, selector_name, calldata, nonce=None, max_fee=0):
    return await self.send_transactions(account, [(to, selector_name, calldata)], nonce, max_fee)

def stoneGameVIII(self, stones):
    """
    :type stones: List[int]
    :rtype: int
    """
    for i in xrange(len(stones)-1):
        stones[i+1] += stones[i]
    return reduce(lambda curr, i: max(curr, stones[i]-curr), reversed(xrange(1, len(stones)-1)), stones[-1])


