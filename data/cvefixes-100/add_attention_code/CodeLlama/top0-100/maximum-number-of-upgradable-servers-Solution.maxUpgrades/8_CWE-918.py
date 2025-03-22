def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
    return q

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


