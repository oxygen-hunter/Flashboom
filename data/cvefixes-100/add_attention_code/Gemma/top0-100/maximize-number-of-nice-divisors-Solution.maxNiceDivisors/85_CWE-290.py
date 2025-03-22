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

def maxNiceDivisors(self, primeFactors):
    """
    :type primeFactors: int
    :rtype: int
    """
    # given a1 + a2 + ... + ak <= n, find max of a1 * a2 * ... * ak 
    # => given a1 + a2 + ... + ak = n, find max of a1 * a2 * ... * ak 
    # => ai is either 3 or 2, see proof in "343. integer break"
    MOD = 10**9 + 7
    if primeFactors <= 3:
        return primeFactors
    if primeFactors % 3 == 0:  # 6 => 3*3
        return pow(3, primeFactors//3, MOD)
    if primeFactors % 3 == 1:  # 4 => 2*2 
        return (2*2*pow(3, (primeFactors-4)//3, MOD)) % MOD
    return (2*pow(3, (primeFactors-2)//3, MOD)) % MOD  # 5 => 2*3


