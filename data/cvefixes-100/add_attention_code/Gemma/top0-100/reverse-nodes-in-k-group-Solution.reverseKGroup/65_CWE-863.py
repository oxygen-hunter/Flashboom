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

def reverseKGroup(self, head, k):
    dummy = ListNode(-1)
    dummy.next = head

    cur, cur_dummy = head, dummy
    length = 0

    while cur:
        next_cur = cur.next
        length = (length + 1) % k

        if length == 0:
            next_dummy = cur_dummy.next
            self.reverse(cur_dummy, cur.next)
            cur_dummy = next_dummy

        cur = next_cur

    return dummy.next



