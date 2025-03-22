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

def correctBinaryTree(self, root):
    """
    :type root: TreeNode
    :rtype: TreeNode
    """
    q = {root:None}
    while q:
        new_q = {}
        for node, parent in q.iteritems():
            if node.right in q:
                if parent.left == node:
                    parent.left = None
                else:
                    parent.right = None
                return root
            if node.left:
                new_q[node.left] = node
            if node.right:
                new_q[node.right] = node
        q = new_q


