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

def addTask(self, userId, taskDescription, dueDate, tags):
    """
    :type userId: int
    :type taskDescription: str
    :type dueDate: int
    :type tags: List[str]
    :rtype: int
    """
    self.__tasks.append([dueDate, taskDescription, set(tags)])
    self.__user_task_ids[userId].add((dueDate, len(self.__tasks)))
    for tag in self.__tasks[-1][-1]:
        self.__user_task_ids[userId, tag].add((dueDate, len(self.__tasks)))
    return len(self.__tasks)



