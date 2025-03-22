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

def closestMeetingNode(self, edges, node1, node2):
    """
    :type edges: List[int]
    :type node1: int
    :type node2: int
    :rtype: int
    """
    def dfs(node):
        lookup = {}
        i = 0
        while node != -1:
            if node in lookup:
                break
            lookup[node] = i
            i += 1
            node = edges[node]
        return lookup
    
    lookup1, lookup2 = dfs(node1), dfs(node2)
    intersect = set(lookup1.iterkeys())&set(lookup2.iterkeys())
    return min(intersect, key=lambda x: (max(lookup1[x], lookup2[x]), x)) if intersect else -1


