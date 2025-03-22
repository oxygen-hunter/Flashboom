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

def maxProfit(self, inventory, orders):
    """
    :type inventory: List[int]
    :type orders: int
    :rtype: int
    """
    MOD = 10**9+7
    def check(inventory, orders, x):
        return count(inventory, x) > orders
    
    def count(inventory, x):
        return sum(count-x+1 for count in inventory if count >= x)

    left, right = 1, max(inventory)
    while left <= right:
        mid = left + (right-left)//2
        if not check(inventory, orders, mid):
            right = mid-1
        else:
            left = mid+1
    # assert(orders-count(inventory, left) >= 0)
    return (sum((left+cnt)*(cnt-left+1)//2 for cnt in inventory if cnt >= left) +
            (left-1)*(orders-count(inventory, left)))% MOD


