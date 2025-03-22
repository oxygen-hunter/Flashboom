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

def maxHeight(self, cuboids):
    """
    :type cuboids: List[List[int]]
    :rtype: int
    """
    for cuboid in cuboids:
        cuboid.sort()
    cuboids.append([0, 0, 0])
    cuboids.sort()
    dp = [0]*len(cuboids)
    for i in xrange(1, len(cuboids)):
        for j in xrange(i):
            if all(cuboids[j][k] <= cuboids[i][k] for k in xrange(3)):
                dp[i] = max(dp[i], dp[j]+cuboids[i][2])
    return max(dp)


