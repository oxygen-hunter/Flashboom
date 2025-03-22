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

def decodeAtIndex(self, S, K):
    """
    :type S: str
    :type K: int
    :rtype: str
    """
    i = 0
    for c in S:
        if c.isdigit():
            i *= int(c)
        else:
            i += 1

    for c in reversed(S):
        K %= i
        if K == 0 and c.isalpha():
            return c

        if c.isdigit():
            i /= int(c)
        else:
            i -= 1



