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

def sortEvenOdd(self, nums):
    """
    :type nums: List[int]
    :rtype: List[int]
    """
    def partition(index, nums):
        for i in xrange(len(nums)):
            j = i
            while nums[i] >= 0:
                j = index(j)
                nums[i], nums[j] = nums[j], ~nums[i]  # processed
        for i in xrange(len(nums)):
            nums[i] = ~nums[i]  # restore values
    
    partition(lambda i: i//2 if i%2 == 0 else (len(nums)+1)//2+i//2, nums)
    nums[:(len(nums)+1)//2], nums[(len(nums)+1)//2:] = sorted(nums[:(len(nums)+1)//2]), sorted(nums[(len(nums)+1)//2:], reverse=True)
    partition(lambda i: 2*i if i < (len(nums)+1)//2 else 1+2*(i-(len(nums)+1)//2), nums)
    return nums



