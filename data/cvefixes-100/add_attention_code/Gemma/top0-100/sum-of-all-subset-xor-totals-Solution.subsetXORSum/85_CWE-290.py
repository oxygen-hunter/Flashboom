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

def subsetXORSum(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    # given there are k (k >= 1) nums of which ith bit is 1,
    # the bit contributes to sum is:
    # (nCr(k, 1) + nCr(k, 3) + ...) * (nCr(n - k, 0) + nCr(n - k, 1) + ...) * 2^i
    # = 2^(k-1) * 2^(n-k) = 2^(n-1) * 2^i
    result = 0
    for x in nums:
        result |= x
    return result * 2**(len(nums)-1)


