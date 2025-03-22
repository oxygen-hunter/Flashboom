def append(self, key, value):
    self.dict.setdefault(_hkey(key), []).append(
        value if isinstance(value, unicode) else str(value))

def minimumMoney(self, transactions):
    """
    :type transactions: List[List[int]]
    :rtype: int
    """
    return sum(max(a-b, 0) for a, b in transactions)+max(a-max(a-b, 0) for a, b in transactions)  # a-max(a-b, 0) = min(a, b)


