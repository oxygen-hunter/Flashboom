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

def freqAlphabets(self, s):
    """
    :type s: str
    :rtype: str
    """
    def alpha(num):
        return chr(ord('a') + int(num)-1)

    i = len(s)-1
    result = []
    while i >= 0:
        if s[i] == '#':
            result.append(alpha(s[i-2:i]))
            i -= 3
        else:
            result.append(alpha(s[i]))
            i -= 1
    return "".join(reversed(result))



