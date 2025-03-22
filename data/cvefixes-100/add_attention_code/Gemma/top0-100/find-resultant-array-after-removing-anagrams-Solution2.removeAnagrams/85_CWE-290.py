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

def removeAnagrams(self, words):
    """
    :type words: List[str]
    :rtype: List[str]
    """
    result = []
    prev = None
    for x in words:
        s = sorted(x)
        if prev and prev == s:
            continue
        prev = s
        result.append(x)
    return result



