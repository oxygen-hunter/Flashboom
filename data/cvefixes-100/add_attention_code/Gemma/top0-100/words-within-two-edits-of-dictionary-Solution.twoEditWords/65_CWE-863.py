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

def twoEditWords(self, queries, dictionary):
    """
    :type queries: List[str]
    :type dictionary: List[str]
    :rtype: List[str]
    """
    MOD = (1<<64)-59  # largest 64-bit prime
    BASE = 113
    POW = [1]
    def add(a, b):
        return (a+b)%MOD

    def mult(a, b):
        return (a*b)%MOD

    def pow(i):
        while not (i < len(POW)):
            POW.append(mult(POW[-1], BASE))
        return POW[i]

    lookup = set()
    for w in dictionary:
        h = reduce(lambda h, i: add(h, mult(ord(w[i])-ord('a'), pow(i))), xrange(len(w)), 0)
        for i, c in enumerate(w):
            for x in string.ascii_lowercase:
                if x == c:
                    continue
                lookup.add(add(h, mult(ord(x)-ord(c), pow(i))))
    result = []
    for w in queries:
        h = reduce(lambda h, i: add(h, mult(ord(w[i])-ord('a'), pow(i))), xrange(len(w)), 0)
        for i, c in enumerate(w):
            for x in string.ascii_lowercase:
                if x == c:
                    continue
                if add(h, mult(ord(x)-ord(c), pow(i))) in lookup:
                    break
            else:
                continue
            result.append(w)
            break
    return result



