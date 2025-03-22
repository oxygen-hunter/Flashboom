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

def summaryRanges(self, nums):
    ranges = []
    if not nums:
        return ranges

    start, end = nums[0], nums[0]
    for i in xrange(1, len(nums) + 1):
        if i < len(nums) and nums[i] == end + 1:
            end = nums[i]
        else:
            interval = str(start)
            if start != end:
                interval += "->" + str(end)
            ranges.append(interval)
            if i < len(nums):
                start = end = nums[i]

    return ranges



