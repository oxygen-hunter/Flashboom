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

def numberOfBeautifulIntegers(self, low, high, k):
    """
    :type low: int
    :type high: int
    :type k: int
    :rtype: int
    """
    def f(x):
        digits = map(int, str(x))
        dp = [[[[0]*k for _ in xrange(2*len(digits)+1)] for _ in xrange(2)] for _ in xrange(2)]
        for tight in xrange(2):
            dp[0][tight][0][0] = 1
        for i in reversed(xrange(len(digits))):
            new_dp = [[[[0]*k for _ in xrange(2*len(digits)+1)] for _ in xrange(2)] for _ in xrange(2)]
            for zero in xrange(2):
                for tight in xrange(2):
                    for d in xrange((digits[i] if tight else 9)+1):
                        new_zero = int(zero and d == 0)
                        new_tight = int(tight and d == digits[i])
                        for diff in xrange(-len(digits), len(digits)+1):
                            new_diff = diff+((1 if d%2 == 0 else -1) if new_zero == 0 else 0)
                            for total in xrange(k):
                                new_total = (total*10+d)%k
                                new_dp[zero][tight][diff][total] += dp[new_zero][new_tight][new_diff][new_total]
            dp = new_dp
        return dp[1][1][0][0]

    return f(high)-f(low-1)


