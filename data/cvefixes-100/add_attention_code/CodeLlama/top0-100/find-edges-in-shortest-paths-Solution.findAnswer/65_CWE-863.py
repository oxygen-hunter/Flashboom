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

def findAnswer(self, n, edges):
    """
    :type n: int
    :type edges: List[List[int]]
    :rtype: List[bool]
    """
    INF = float("inf")
    def dijkstra(start):
        best = [INF]*len(adj)
        best[start] = 0
        min_heap = [(0, start)]
        while min_heap:
            curr, u = heapq.heappop(min_heap)
            if curr > best[u]:
                continue
            for v, w in adj[u]:     
                if best[v] <= curr+w:
                    continue
                best[v] = curr+w
                heapq.heappush(min_heap, (best[v], v))
        return best

    adj = [[] for _ in xrange(n)]
    for u, v, w in edges:
        adj[u].append((v, w))
        adj[v].append((u, w))
    dist1 = dijkstra(0)
    dist2 = dijkstra(n-1)
    return [(dist1[u] != INF != dist2[v] and dist1[u]+w+dist2[v] == dist1[n-1]) or
            (dist2[u] != INF != dist1[v] and dist2[u]+w+dist1[v] == dist2[0])
            for i, (u, v, w) in enumerate(edges)]


