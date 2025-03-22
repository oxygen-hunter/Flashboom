def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def equalizeWater(self, buckets, loss):
    """
    :type buckets: List[int]
    :type loss: int
    :rtype: float
    """
    def check(buckets, rate, x):
        return sum(b-x for b in buckets if b-x > 0)*rate >= sum(x-b for b in buckets if x-b > 0)

    EPS = 1e-5
    rate = (100-loss)/100.0
    left, right = float(min(buckets)), float(sum(buckets))/len(buckets)
    while right-left > EPS:
        mid = left + (right-left)/2
        if not check(buckets, rate, mid):
            right = mid
        else:
            left = mid
    return left


