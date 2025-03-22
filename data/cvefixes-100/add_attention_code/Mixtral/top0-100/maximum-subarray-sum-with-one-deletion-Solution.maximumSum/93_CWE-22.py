def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def maximumSum(self, arr):
    """
    :type arr: List[int]
    :rtype: int
    """
    result, prev, curr = float("-inf"), float("-inf"), float("-inf")
    for x in arr:
        curr = max(prev, curr+x, x)
        result = max(result, curr)
        prev = max(prev+x, x)
    return result


