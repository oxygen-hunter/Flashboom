async def send_transactions(self, account, calls, nonce=None, max_fee=0):
    if nonce is None:
        execution_info = await account.get_nonce().call()
        nonce, = execution_info.result

    build_calls = []
    for call in calls:
        build_call = list(call)
        build_call[0] = hex(build_call[0])
        build_calls.append(build_call)

    (call_array, calldata, sig_r, sig_s) = self.signer.sign_transaction(hex(account.contract_address), build_calls, nonce, max_fee)
    return await account.__execute__(call_array, calldata, nonce).invoke(signature=[sig_r, sig_s])

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


