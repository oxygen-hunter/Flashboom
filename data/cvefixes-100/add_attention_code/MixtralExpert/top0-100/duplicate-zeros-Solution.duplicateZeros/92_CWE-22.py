def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

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


