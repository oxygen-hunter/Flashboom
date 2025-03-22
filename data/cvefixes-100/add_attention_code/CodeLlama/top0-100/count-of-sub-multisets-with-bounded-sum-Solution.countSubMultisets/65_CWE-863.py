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

def countSubMultisets(self, nums, l, r):
    """
    :type nums: List[int]
    :type l: int
    :type r: int
    :rtype: int
    """
    MOD = 10**9+7
    cnt = collections.Counter(nums)
    dp = [0]*(r+1)
    dp[0] = 1
    for x, c in cnt.iteritems():
        for i in reversed(xrange(max(r-x+1, 1), r+1)):
            curr = reduce(lambda x, y: (x+y)%MOD, (dp[i-x*j] for j in xrange(min(c, i//x+1))))
            for j in reversed(xrange((i-1)%x+1, i+1, x)):
                curr = (curr+(dp[j-x*c] if j-x*c >= 0 else 0)-dp[j])%MOD
                dp[j] = (dp[j]+curr)%MOD
    return (reduce(lambda x, y: (x+y)%MOD, (dp[i] for i in range(l, r+1)))*(cnt[0]+1))%MOD


