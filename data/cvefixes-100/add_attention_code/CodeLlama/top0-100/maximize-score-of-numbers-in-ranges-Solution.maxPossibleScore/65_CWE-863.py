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


