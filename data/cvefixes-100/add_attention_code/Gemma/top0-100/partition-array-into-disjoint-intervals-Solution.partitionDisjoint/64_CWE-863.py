async def send_transaction(self, account, to, selector_name, calldata, nonce=None, max_fee=0):
    return await self.send_transactions(account, [(to, selector_name, calldata)], nonce, max_fee)

def partitionDisjoint(self, A):
    """
    :type A: List[int]
    :rtype: int
    """
    B = A[:]
    for i in reversed(xrange(len(A)-1)):
        B[i] = min(B[i], B[i+1])
    p_max = 0
    for i in xrange(1, len(A)):
        p_max = max(p_max, A[i-1])
        if p_max <= B[i]:
            return i



