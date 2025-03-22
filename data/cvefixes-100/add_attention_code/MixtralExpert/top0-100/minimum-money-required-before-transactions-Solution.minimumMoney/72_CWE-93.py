def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

def minimumMoney(self, transactions):
    """
    :type transactions: List[List[int]]
    :rtype: int
    """
    return sum(max(a-b, 0) for a, b in transactions)+max(a-max(a-b, 0) for a, b in transactions)  # a-max(a-b, 0) = min(a, b)


