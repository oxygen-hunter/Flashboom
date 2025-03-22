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

def maxProduct(self, s):
    """
    :type s: str
    :rtype: int
    """
    def palindromic_subsequence_length(s, mask):
        result = 0
        left, right = 0, len(s)-1
        left_bit, right_bit = 1<<left, 1<<right
        while left <= right:
            if mask&left_bit == 0:
                left, left_bit = left+1, left_bit<<1
            elif mask&right_bit == 0:
                right, right_bit = right-1, right_bit>>1
            elif s[left] == s[right]:
                result += 1 if left == right else 2
                left, left_bit = left+1, left_bit<<1
                right, right_bit = right-1, right_bit>>1
            else:
                return 0
        return result
    
    dp = [palindromic_subsequence_length(s, mask) for mask in xrange(1<<len(s))]
    result = 0
    for mask in xrange(len(dp)):
        if dp[mask]*(len(s)-dp[mask]) <= result:  # optimize
            continue
        # submask enumeration:
        # => sum(nCr(n, k) * 2^k for k in xrange(n+1)) = (1 + 2)^n = 3^n
        # => Time: O(3^n), see https://cp-algorithms.com/algebra/all-submasks.html
        submask = inverse_mask = (len(dp)-1)^mask
        while submask:
            result = max(result, dp[mask]*dp[submask])
            submask = (submask-1)&inverse_mask
    return result


