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

def minNonZeroProduct(self, p):
    """
    :type p: int
    :rtype: int
    """
    MOD = 10**9+7

    # max_num = 2^p-1
    max_num_mod = (pow(2, p, MOD)-1)%MOD  # max_num % MOD

    # pair_product = max_num-1
    pair_product_mod = (max_num_mod-1)%MOD  # (max_num_mod-1) % MOD

    # since pair_product^MOD % MOD = pair_product_mod^MOD % MOD  = pair_product_mod
    # => pair_product_mod^(MOD-1) % MOD = 1
    # => pair_product_mod^(pair_cnt) % MOD = pair_product_mod^(pair_cnt%(MOD-1)) %MOD
    pair_cnt_mod_m_1 = (pow(2, p-1, MOD-1)-1) % (MOD-1)  # pair_cnt%(MOD-1)

    # the ans is:
    #   max_num * pair_product^pair_cnt % MOD
    # = max_num_mod * pair_product_mod^(pair_cnt_mod_m_1) % MOD
    return (max_num_mod*pow(pair_product_mod, pair_cnt_mod_m_1, MOD)) % MOD


