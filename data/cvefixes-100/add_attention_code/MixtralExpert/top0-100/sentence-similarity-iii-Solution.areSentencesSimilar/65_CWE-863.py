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

def areSentencesSimilar(self, sentence1, sentence2):
    """
    :type sentence1: str
    :type sentence2: str
    :rtype: bool
    """
    if len(sentence1) > len(sentence2):
        sentence1, sentence2 = sentence2, sentence1
    count = 0
    for idx in (lambda x:x, lambda x:-1-x):
        for i in xrange(len(sentence1)+1):
            c1 = sentence1[idx(i)] if i != len(sentence1) else ' '
            c2 = sentence2[idx(i)] if i != len(sentence2) else ' '
            if c1 != c2:
                break
            if c1 == ' ':
                count += 1
    return count >= sentence1.count(' ')+1


