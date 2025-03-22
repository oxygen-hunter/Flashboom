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

def shortestBridge(self, A):
    """
    :type A: List[List[int]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

    def get_islands(A):
        islands = []
        done = set()
        for r, row in enumerate(A):
            for c, val in enumerate(row):
                if val == 0 or (r, c) in done:
                    continue
                s = [(r, c)]
                lookup = set(s)
                while s:
                    node = s.pop()
                    for d in directions:
                        nei = node[0]+d[0], node[1]+d[1]
                        if not (0 <= nei[0] < len(A) and 0 <= nei[1] < len(A[0])) or \
                           nei in lookup or A[nei[0]][nei[1]] == 0:
                            continue
                        s.append(nei)
                        lookup.add(nei)
                done |= lookup
                islands.append(lookup)
                if len(islands) == 2:
                    break
        return islands

    lookup, target = get_islands(A)
    q = collections.deque([(node, 0) for node in lookup])
    while q:
        node, dis = q.popleft()
        if node in target:
            return dis-1
        for d in directions:
            nei = node[0]+d[0], node[1]+d[1]
            if not (0 <= nei[0] < len(A) and 0 <= nei[1] < len(A[0])) or \
               nei in lookup:
                continue
            q.append((nei, dis+1))
            lookup.add(nei)


