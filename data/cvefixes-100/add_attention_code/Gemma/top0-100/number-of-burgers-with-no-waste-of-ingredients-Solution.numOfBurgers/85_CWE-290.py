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

def numOfBurgers(self, tomatoSlices, cheeseSlices):
    """
    :type tomatoSlices: int
    :type cheeseSlices: int
    :rtype: List[int]
    """
    # let the number of jumbo burger be x, the number of small burger be y:
    #   4x + 2y = t
    #   x + y = c
    #   =>
    #   x = t/2-c
    #   y = 2c-t/2
    # since x, y are natural numbers
    #   => t/2 is integer, t/2-c >= 0, 2c-t/2 >= 0
    #   => t%2 == 0, 2c <= t <= 4c
    return [tomatoSlices//2-cheeseSlices, 2*cheeseSlices - tomatoSlices//2] \
           if tomatoSlices%2 == 0 and 2*cheeseSlices <= tomatoSlices <= 4*cheeseSlices \
           else []


