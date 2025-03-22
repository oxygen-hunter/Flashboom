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

def betterCompression(self, compressed):
    """
    :type compressed: str
    :rtype: str
    """
    cnt = [0]*26
    x, curr = -1, 0
    for i in xrange(len(compressed)):
        if not compressed[i].isdigit():
            x = ord(compressed[i])-ord('a')
            continue
        curr = curr*10+int(compressed[i])
        if i+1 == len(compressed) or not compressed[i+1].isdigit():
            cnt[x] += curr
            curr = 0
    return "".join("%s%s" % (chr(ord('a')+i), x) for i, x in enumerate(cnt) if x)


