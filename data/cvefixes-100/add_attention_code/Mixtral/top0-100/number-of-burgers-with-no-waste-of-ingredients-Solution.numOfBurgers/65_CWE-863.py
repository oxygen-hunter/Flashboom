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

def numOfBurgers(self, tomatoSlices, cheeseSlices):
    """
    :type tomatoSlices: int
    :type cheeseSlices: int
    :rtype: List[int]
    """
    # let the number of jumbo burger be x, the number of small burger be y:
    #   4x + 2y = t
    #   x + y = c
    #   =>
    #   x = t/2-c
    #   y = 2c-t/2
    # since x, y are natural numbers
    #   => t/2 is integer, t/2-c >= 0, 2c-t/2 >= 0
    #   => t%2 == 0, 2c <= t <= 4c
    return [tomatoSlices//2-cheeseSlices, 2*cheeseSlices - tomatoSlices//2] \
           if tomatoSlices%2 == 0 and 2*cheeseSlices <= tomatoSlices <= 4*cheeseSlices \
           else []


