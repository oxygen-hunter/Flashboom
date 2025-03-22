def __init__(self, private_key):
    self.signer = Signer(private_key)
    self.public_key = self.signer.public_key

def findNumber(self):
    """
    :rtype: int
    """
    return reduce(lambda accu, x: accu|x, (1<<i for i in xrange(30) if commonSetBits(1<<i)))


