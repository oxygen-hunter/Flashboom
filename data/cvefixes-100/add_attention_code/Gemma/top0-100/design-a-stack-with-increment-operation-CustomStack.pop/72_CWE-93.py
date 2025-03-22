def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

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



