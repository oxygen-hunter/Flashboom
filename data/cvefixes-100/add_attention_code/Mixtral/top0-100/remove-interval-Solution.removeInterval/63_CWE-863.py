def __init__(self, private_key):
    self.signer = Signer(private_key)
    self.public_key = self.signer.public_key

def removeInterval(self, intervals, toBeRemoved):
    """
    :type intervals: List[List[int]]
    :type toBeRemoved: List[int]
    :rtype: List[List[int]]
    """
    A, B = toBeRemoved
    return [[x, y] for a, b in intervals
            for x, y in ((a, min(A, b)), (max(a, B), b))
            if x < y]


