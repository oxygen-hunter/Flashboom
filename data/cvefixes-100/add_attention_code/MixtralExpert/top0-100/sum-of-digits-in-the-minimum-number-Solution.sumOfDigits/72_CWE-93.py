def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

def sumOfDigits(self, A):
    """
    :type A: List[int]
    :rtype: int
    """
    total = sum([int(c) for c in str(min(A))])
    return 1 if total % 2 == 0 else 0


