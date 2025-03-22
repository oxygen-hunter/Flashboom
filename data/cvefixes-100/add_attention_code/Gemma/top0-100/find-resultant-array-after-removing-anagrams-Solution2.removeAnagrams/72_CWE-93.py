def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

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



