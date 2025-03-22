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

def minCost(self, startPos, homePos, rowCosts, colCosts):
    """
    :type startPos: List[int]
    :type homePos: List[int]
    :type rowCosts: List[int]
    :type colCosts: List[int]
    :rtype: int
    """
    [x0, y0], [x1, y1] = startPos, homePos
    return (sum(rowCosts[i] for i in xrange(min(x0, x1), max(x0, x1)+1))-rowCosts[x0]) + \
           (sum(colCosts[i] for i in xrange(min(y0, y1), max(y0, y1)+1))-colCosts[y0])


