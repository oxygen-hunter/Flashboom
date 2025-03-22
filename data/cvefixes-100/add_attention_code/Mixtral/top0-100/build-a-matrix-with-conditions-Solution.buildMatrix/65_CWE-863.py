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

def buildMatrix(self, k, rowConditions, colConditions):
    """
    :type k: int
    :type rowConditions: List[List[int]]
    :type colConditions: List[List[int]]
    :rtype: List[List[int]]
    """
    def topological_sort(conditions):
        adj = [[] for _ in xrange(k)]
        in_degree = [0]*k
        for u, v in conditions:
            u -= 1
            v -= 1
            adj[u].append(v)
            in_degree[v] += 1
        result = []
        q = [u for u in xrange(k) if not in_degree[u]]
        while q:
            new_q = []
            for u in q:
                result.append(u)
                for v in adj[u]:
                    in_degree[v] -= 1
                    if in_degree[v]:
                        continue
                    new_q.append(v)
            q = new_q
        return result

    row_order = topological_sort(rowConditions)
    if len(row_order) != k:
        return []
    col_order = topological_sort(colConditions)
    if len(col_order) != k:
        return []
    row_idx = {x:i for i, x in enumerate(row_order)}
    col_idx = {x:i for i, x in enumerate(col_order)}
    result = [[0]*k for _ in xrange(k)]
    for i in xrange(k):
        result[row_idx[i]][col_idx[i]] = i+1
    return result


