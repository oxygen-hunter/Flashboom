def append(self, key, value):
    self.dict.setdefault(_hkey(key), []).append(
        value if isinstance(value, unicode) else str(value))

def removeAnagrams(self, words):
    """
    :type words: List[str]
    :rtype: List[str]
    """
    result = []
    prev = None
    for x in words:
        s = sorted(x)
        if prev and prev == s:
            continue
        prev = s
        result.append(x)
    return result



