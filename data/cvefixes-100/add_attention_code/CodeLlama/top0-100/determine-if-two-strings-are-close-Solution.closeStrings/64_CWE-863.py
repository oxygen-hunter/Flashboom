async def send_transaction(self, account, to, selector_name, calldata, nonce=None, max_fee=0):
    return await self.send_transactions(account, [(to, selector_name, calldata)], nonce, max_fee)

def closeStrings(self, word1, word2):
    """
    :type word1: str
    :type word2: str
    :rtype: bool
    """
    if len(word1) != len(word2):
        return False 
    
    cnt1, cnt2 = collections.Counter(word1), collections.Counter(word2)   # Reuse of keys
    return set(cnt1.iterkeys()) == set(cnt2.iterkeys()) and \
           collections.Counter(cnt1.itervalues()) == collections.Counter(cnt2.itervalues())


