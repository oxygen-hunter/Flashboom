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

def countMatchingSubarrays(self, nums, pattern):
    """
    :type nums: List[int]
    :type pattern: List[int]
    :rtype: int
    """
    def getPrefix(pattern):
        prefix = [-1]*len(pattern)
        j = -1
        for i in xrange(1, len(pattern)):
            while j+1 > 0 and pattern[j+1] != pattern[i]:
                j = prefix[j]
            if pattern[j+1] == pattern[i]:
                j += 1
            prefix[i] = j
        return prefix

    def KMP(text, pattern):
        prefix = getPrefix(pattern)
        j = -1
        for i, x in enumerate(text):
            while j+1 > 0 and pattern[j+1] != x:
                j = prefix[j]
            if pattern[j+1] == x:
                j += 1
            if j+1 == len(pattern):
                yield i-j
                j = prefix[j]

    return sum(1 for _ in KMP((cmp(nums[i+1], nums[i]) for i in xrange(len(nums)-1)), pattern))


