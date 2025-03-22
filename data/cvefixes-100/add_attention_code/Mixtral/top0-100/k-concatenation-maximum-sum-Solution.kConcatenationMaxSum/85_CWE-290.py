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

def kConcatenationMaxSum(self, arr, k):
    """
    :type arr: List[int]
    :type k: int
    :rtype: int
    """
    def max_sub_k_array(arr, k):
        result, curr = float("-inf"), float("-inf")
        for _ in xrange(k):
            for x in arr:
                curr = max(curr+x, x)
                result = max(result, curr)
        return result
    
    MOD = 10**9+7
    if k == 1:
        return max(max_sub_k_array(arr, 1), 0) % MOD
    return (max(max_sub_k_array(arr, 2), 0) + (k-2)*max(sum(arr), 0)) % MOD


