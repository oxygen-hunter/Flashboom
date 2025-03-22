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

def totalMoney(self, n):
    """
    :type n: int
    :rtype: int
    """
    def arithmetic_sequence_sum(a, d, n):
        return (2*a + (n-1)*d) * n //2

    cost, day = 1, 7
    first_week_cost = arithmetic_sequence_sum(cost, cost, day)
    week, remain_day = divmod(n, day)
    return arithmetic_sequence_sum(first_week_cost, cost*day, week) + \
           arithmetic_sequence_sum(cost*(week+1), cost, remain_day)


