def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

def popFront(self):
    """
    :rtype: int
    """
    val = (self.__left or collections.deque([-1])).popleft()
    self.__balance()
    return val



