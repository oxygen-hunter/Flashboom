def __setitem__(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                             str(value)]

def haveConflict(self, event1, event2):
    """
    :type event1: List[str]
    :type event2: List[str]
    :rtype: bool
    """
    return max(event1[0], event2[0]) <= min(event1[1], event2[1])


