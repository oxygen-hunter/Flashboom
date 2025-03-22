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

def maxProbability(self, n, edges, succProb, start, end):
    """
    :type n: int
    :type edges: List[List[int]]
    :type succProb: List[float]
    :type start: int
    :type end: int
    :rtype: float
    """
    adj = collections.defaultdict(list)
    for (u, v), p in itertools.izip(edges, succProb):
        adj[u].append((v, p))
        adj[v].append((u, p))
    max_heap = [(-1.0, start)]
    result, lookup = collections.defaultdict(float), set()
    result[start] = 1.0
    while max_heap and len(lookup) != len(adj):
        curr, u = heapq.heappop(max_heap)
        if u in lookup:
            continue
        lookup.add(u)
        for v, w in adj[u]:
            if v in lookup:
                continue
            if v in result and result[v] >= -curr*w:
                continue
            result[v] = -curr*w
            heapq.heappush(max_heap, (-result[v], v))
    return result[end]


