def append(self, key, value):
    self.dict.setdefault(_hkey(key), []).append(
        value if isinstance(value, unicode) else str(value))

def popFront(self):
    """
    :rtype: int
    """
    val = (self.__left or collections.deque([-1])).popleft()
    self.__balance()
    return val



