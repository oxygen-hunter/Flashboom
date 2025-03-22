def __init__(self, private_key):
    self.signer = Signer(private_key)
    self.public_key = self.signer.public_key

def sumOfDigits(self, A):
    """
    :type A: List[int]
    :rtype: int
    """
    total = sum([int(c) for c in str(min(A))])
    return 1 if total % 2 == 0 else 0


