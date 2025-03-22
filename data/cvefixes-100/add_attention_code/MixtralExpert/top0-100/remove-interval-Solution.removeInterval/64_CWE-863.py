async def send_transaction(self, account, to, selector_name, calldata, nonce=None, max_fee=0):
    return await self.send_transactions(account, [(to, selector_name, calldata)], nonce, max_fee)

def removeInterval(self, intervals, toBeRemoved):
    """
    :type intervals: List[List[int]]
    :type toBeRemoved: List[int]
    :rtype: List[List[int]]
    """
    A, B = toBeRemoved
    return [[x, y] for a, b in intervals
            for x, y in ((a, min(A, b)), (max(a, B), b))
            if x < y]


