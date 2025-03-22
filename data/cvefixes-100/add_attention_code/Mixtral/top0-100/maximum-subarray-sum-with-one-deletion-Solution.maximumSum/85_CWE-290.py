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


