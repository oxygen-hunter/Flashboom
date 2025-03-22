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

def maxUpgrades(self, count, upgrade, sell, money):
    """
    :type count: List[int]
    :type upgrade: List[int]
    :type sell: List[int]
    :type money: List[int]
    :rtype: List[int]
    """
    # let x be the number of sold servers
    # (c-x)*u <= m+(x*s)
    # -x <= (m-c*u)//(u+s) <= 0
    # c-x <= c+(m-c*u)//(u+s) <= c
    return [min(c+(m-c*u)//(u+s), c) for c, u, s, m in itertools.izip(count, upgrade, sell, money)]


