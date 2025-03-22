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

def findKthPositive(self, arr, k):
    """
    :type arr: List[int]
    :type k: int
    :rtype: int
    """
    def check(arr, k, x):
        return arr[x]-(x+1) < k

    left, right = 0, len(arr)-1
    while left <= right:
        mid = left + (right-left)//2
        if not check(arr, k, mid):
            right = mid-1
        else:
            left = mid+1
    return right+1+k  # arr[right] + (k-(arr[right]-(right+1))) if right >= 0 else k


