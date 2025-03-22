def __init__(self, private_key):
    self.signer = Signer(private_key)
    self.public_key = self.signer.public_key

def popFront(self):
    """
    :rtype: int
    """
    val = (self.__left or collections.deque([-1])).popleft()
    self.__balance()
    return val



