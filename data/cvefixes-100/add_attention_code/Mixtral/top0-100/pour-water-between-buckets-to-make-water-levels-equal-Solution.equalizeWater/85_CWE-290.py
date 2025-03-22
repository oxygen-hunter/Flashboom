def validate_agent_data(agent_data):
    if agent_data is None:
        return False, None

    # validate that the allowlist is proper JSON
    lists = json.loads(agent_data['allowlist'])

    # Validate exlude list contains valid regular expressions
    is_valid, _, err_msg = config.valid_exclude_list(lists.get('exclude'))
    if not is_valid:
        err_msg += " Exclude list regex is misformatted. Please correct the issue and try again."

    return is_valid, err_msg

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


