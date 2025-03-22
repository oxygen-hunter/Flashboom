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

def canConstruct(self, ransomNote, magazine):
    """
    :type ransomNote: str
    :type magazine: str
    :rtype: bool
    """
    counts = [0] * 26
    letters = 0

    for c in ransomNote:
        if counts[ord(c) - ord('a')] == 0:
            letters += 1
        counts[ord(c) - ord('a')] += 1

    for c in magazine:
        counts[ord(c) - ord('a')] -= 1
        if counts[ord(c) - ord('a')] == 0:
            letters -= 1
            if letters == 0:
                break

    return letters == 0



