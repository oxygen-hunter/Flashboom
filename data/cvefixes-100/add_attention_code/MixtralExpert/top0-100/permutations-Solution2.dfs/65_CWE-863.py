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

def dfs(self, nums, path, res):
    if not nums:
        res.append(path)

    for i in xrange(len(nums)):
        # e.g., [1, 2, 3]: 3! = 6 cases
        # idx -> nums, path
        # 0 -> [2, 3], [1] -> 0: [3], [1, 2] -> [], [1, 2, 3]
        #                  -> 1: [2], [1, 3] -> [], [1, 3, 2]
        #
        # 1 -> [1, 3], [2] -> 0: [3], [2, 1] -> [], [2, 1, 3]
        #                  -> 1: [1], [2, 3] -> [], [2, 3, 1]
        #
        # 2 -> [1, 2], [3] -> 0: [2], [3, 1] -> [], [3, 1, 2]
        #                  -> 1: [1], [3, 2] -> [], [3, 2, 1]
        self.dfs(nums[:i] + nums[i+1:], path + [nums[i]], res)


