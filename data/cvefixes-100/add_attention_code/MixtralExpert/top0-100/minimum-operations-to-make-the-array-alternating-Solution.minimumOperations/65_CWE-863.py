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

def minimumOperations(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    even_top = collections.Counter(nums[i] for i in xrange(0, len(nums), 2)).most_common(2)  # Time: O(nlogk)
    odd_top = collections.Counter(nums[i] for i in xrange(1, len(nums), 2)).most_common(2)  # Time: O(nlogk)
    if not odd_top or even_top[0][0] != odd_top[0][0]:
        return len(nums)-even_top[0][1]-(odd_top[0][1] if odd_top else 0)
    return min(len(nums)-even_top[0][1]-(odd_top[1][1] if len(odd_top) == 2 else 0),
               len(nums)-odd_top[0][1]-(even_top[1][1] if len(even_top) == 2 else 0))


