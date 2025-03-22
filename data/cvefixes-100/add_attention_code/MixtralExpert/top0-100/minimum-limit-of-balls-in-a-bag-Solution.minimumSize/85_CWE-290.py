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

def minimumSize(self, nums, maxOperations):
    """
    :type nums: List[int]
    :type maxOperations: int
    :rtype: int
    """
    def check(nums, maxOperations, x):
        return sum((num+x-1)//x-1 for num in nums) <= maxOperations

    left, right = 1, max(nums)
    while left <= right:
        mid = left + (right-left)//2
        if check(nums, maxOperations, mid):
            right = mid-1
        else:
            left = mid+1
    return left


