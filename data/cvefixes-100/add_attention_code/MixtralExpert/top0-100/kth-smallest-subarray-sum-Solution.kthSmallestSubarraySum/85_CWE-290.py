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

def kthSmallestSubarraySum(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    def check(nums, k, x):
        cnt = curr = left = 0
        for right in xrange(len(nums)):
            curr += nums[right]
            while curr > x:
                curr -= nums[left]
                left += 1
            cnt += right-left+1
        return cnt >= k

    left, right = min(nums), sum(nums)
    while left <= right:
        mid = left + (right-left)//2
        if check(nums, k, mid):
            right = mid-1
        else:
            left = mid+1
    return left


