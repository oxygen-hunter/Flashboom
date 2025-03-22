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

def getNumberOfBacklogOrders(self, orders):
    """
    :type orders: List[List[int]]
    :rtype: int
    """
    MOD = 10**9 + 7
    buy, sell  = [], []  # max_heap, min_heap
    for p, a, t in orders:
        if t == 0:
            heapq.heappush(buy, [-p, a])
        else:
            heapq.heappush(sell, [p, a])
        while sell and buy and sell[0][0] <= -buy[0][0]:
            k = min(buy[0][1], sell[0][1])
            tmp = heapq.heappop(buy)
            tmp[1] -= k
            if tmp[1]:
                heapq.heappush(buy, tmp)
            tmp = heapq.heappop(sell)
            tmp[1] -= k
            if tmp[1]:
                heapq.heappush(sell, tmp)
    return reduce(lambda x, y: (x+y) % MOD, (a for _, a in buy + sell))


