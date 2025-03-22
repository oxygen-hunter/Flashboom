async def send_transaction(self, account, to, selector_name, calldata, nonce=None, max_fee=0):
    return await self.send_transactions(account, [(to, selector_name, calldata)], nonce, max_fee)

def canConstruct(self, ransomNote, magazine):
    """
    :type ransomNote: str
    :type magazine: str
    :rtype: bool
    """
    counts = [0] * 26
    letters = 0

    for c in ransomNote:
        if counts[ord(c) - ord('a')] == 0:
            letters += 1
        counts[ord(c) - ord('a')] += 1

    for c in magazine:
        counts[ord(c) - ord('a')] -= 1
        if counts[ord(c) - ord('a')] == 0:
            letters -= 1
            if letters == 0:
                break

    return letters == 0



