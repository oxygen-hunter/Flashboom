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

def smallestSubsequence(self, s, k, letter, repetition):
    """
    :type s: str
    :type k: int
    :type letter: str
    :type repetition: int
    :rtype: str
    """
    stk = []
    suffix = [0]*(len(s)+1)
    for i in reversed(xrange(len(suffix)-1)):
        suffix[i] = suffix[i+1]+(s[i] == letter)
    for i, c in enumerate(s): 
        while stk and stk[-1] > c and len(stk)+(len(s)-i) > k and (stk[-1] != letter or repetition+1 <= suffix[i]):
            repetition += (stk.pop() == letter)
        if len(stk) < min(k-(repetition-(c == letter)), k):
            repetition -= (c == letter)
            stk.append(c)
    return "".join(stk)


