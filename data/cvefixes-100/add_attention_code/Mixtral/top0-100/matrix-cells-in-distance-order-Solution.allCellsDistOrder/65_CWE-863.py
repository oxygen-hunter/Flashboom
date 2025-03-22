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

def allCellsDistOrder(self, R, C, r0, c0):
    """
    :type R: int
    :type C: int
    :type r0: int
    :type c0: int
    :rtype: List[List[int]]
    """
    def append(R, C, r, c, result):
        if 0 <= r < R and 0 <= c < C:
            result.append([r, c])
        
    result = [[r0, c0]]
    for d in xrange(1, R+C):
        append(R, C, r0-d, c0, result)
        for x in xrange(-d+1, d):
            append(R, C, r0+x, c0+abs(x)-d, result)
            append(R, C, r0+x, c0+d-abs(x), result)
        append(R, C, r0+d, c0, result)
    return result


