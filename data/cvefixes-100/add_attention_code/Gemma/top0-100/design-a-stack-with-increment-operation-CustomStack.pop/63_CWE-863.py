def __init__(self, private_key):
    self.signer = Signer(private_key)
    self.public_key = self.signer.public_key

def pop(self):
    """
    :rtype: int
    """
    if not self.__stk:
        return -1
    x, inc = self.__stk.pop()
    if self.__stk:
        self.__stk[-1][1] += inc
    return x + inc



