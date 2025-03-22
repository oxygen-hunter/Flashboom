def append(self, key, value):
    self.dict.setdefault(_hkey(key), []).append(
        value if isinstance(value, unicode) else str(value))

def add(self, num):
    """
    :type num: int
    :rtype: None
    """
    if not num:
        self.__accu = [1]
        return
    self.__accu.append(self.__accu[-1]*num)             



