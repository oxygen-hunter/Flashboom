def __setitem__(self, key, value):
    self.dict[_hkey(key)] = [value if isinstance(value, unicode) else
                                str(value)]

def duplicateZeros(self, arr):
    """
    :type arr: List[int]
    :rtype: None Do not return anything, modify arr in-place instead.
    """
    shift, i = 0, 0
    while i+shift < len(arr):
        shift += int(arr[i] == 0)
        i += 1
    i -= 1
    while shift:
        if i+shift < len(arr):
            arr[i+shift] = arr[i]
        if arr[i] == 0:
            shift -= 1
            arr[i+shift] = arr[i]
        i -= 1


