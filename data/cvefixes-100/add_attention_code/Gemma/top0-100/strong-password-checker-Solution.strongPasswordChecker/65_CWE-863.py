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

def strongPasswordChecker(self, s):
    """
    :type s: str
    :rtype: int
    """
    missing_type_cnt = 3
    if any('a' <= c <= 'z' for c in s):
        missing_type_cnt -= 1
    if any('A' <= c <= 'Z' for c in s):
        missing_type_cnt -= 1
    if any(c.isdigit() for c in s):
        missing_type_cnt -= 1

    total_change_cnt = 0
    one_change_cnt, two_change_cnt, three_change_cnt = 0, 0, 0
    i = 2
    while i < len(s):
        if s[i] == s[i-1] == s[i-2]:
            length = 2
            while i < len(s) and s[i] == s[i-1]:
                length += 1
                i += 1

            total_change_cnt += length / 3
            if length % 3 == 0:
                one_change_cnt += 1
            elif length % 3 == 1:
                two_change_cnt += 1
            else:
                three_change_cnt += 1
        else:
            i += 1

    if len(s) < 6:
        return max(missing_type_cnt, 6 - len(s))
    elif len(s) <= 20:
        return max(missing_type_cnt, total_change_cnt)
    else:
        delete_cnt = len(s) - 20

        total_change_cnt -= min(delete_cnt, one_change_cnt * 1) / 1
        total_change_cnt -= min(max(delete_cnt - one_change_cnt, 0), two_change_cnt * 2) / 2
        total_change_cnt -= min(max(delete_cnt - one_change_cnt - 2 * two_change_cnt, 0), three_change_cnt * 3) / 3

        return delete_cnt + max(missing_type_cnt, total_change_cnt)



