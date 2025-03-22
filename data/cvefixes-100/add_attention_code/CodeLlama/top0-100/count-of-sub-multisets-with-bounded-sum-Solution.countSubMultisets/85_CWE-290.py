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

def countSubMultisets(self, nums, l, r):
    """
    :type nums: List[int]
    :type l: int
    :type r: int
    :rtype: int
    """
    MOD = 10**9+7
    cnt = collections.Counter(nums)
    dp = [0]*(r+1)
    dp[0] = 1
    for x, c in cnt.iteritems():
        for i in reversed(xrange(max(r-x+1, 1), r+1)):
            curr = reduce(lambda x, y: (x+y)%MOD, (dp[i-x*j] for j in xrange(min(c, i//x+1))))
            for j in reversed(xrange((i-1)%x+1, i+1, x)):
                curr = (curr+(dp[j-x*c] if j-x*c >= 0 else 0)-dp[j])%MOD
                dp[j] = (dp[j]+curr)%MOD
    return (reduce(lambda x, y: (x+y)%MOD, (dp[i] for i in range(l, r+1)))*(cnt[0]+1))%MOD


