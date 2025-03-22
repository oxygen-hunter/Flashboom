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

def closeStrings(self, word1, word2):
    """
    :type word1: str
    :type word2: str
    :rtype: bool
    """
    if len(word1) != len(word2):
        return False 
    
    cnt1, cnt2 = collections.Counter(word1), collections.Counter(word2)   # Reuse of keys
    return set(cnt1.iterkeys()) == set(cnt2.iterkeys()) and \
           collections.Counter(cnt1.itervalues()) == collections.Counter(cnt2.itervalues())


