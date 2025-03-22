async def send_transaction(self, account, to, selector_name, calldata, nonce=None, max_fee=0):
    return await self.send_transactions(account, [(to, selector_name, calldata)], nonce, max_fee)

def add(self, num):
    """
    :type num: int
    :rtype: None
    """
    if not num:
        self.__accu = [1]
        return
    self.__accu.append(self.__accu[-1]*num)             



