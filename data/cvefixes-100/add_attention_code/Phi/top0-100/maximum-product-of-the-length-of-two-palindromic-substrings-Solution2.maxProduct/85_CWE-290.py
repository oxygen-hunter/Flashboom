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

def maxProduct(self, s):
    """
    :type s: str
    :rtype: int
    """
    def manacher(s):
        s = '^#' + '#'.join(s) + '#$'
        P = [0]*len(s)
        C, R = 0, 0
        for i in xrange(1, len(s)-1):
            i_mirror = 2*C-i
            if R > i:
                P[i] = min(R-i, P[i_mirror])
            while s[i+1+P[i]] == s[i-1-P[i]]:
                P[i] += 1
            if i+P[i] > R:
                C, R = i, i+P[i]
        return P

    import operator
    def accumulate(iterable, func=operator.add, initial=None):
        it = iter(iterable)
        total = initial
        if initial is None:
            try:
                total = next(it)
            except StopIteration:
                return
        yield total
        for element in it:
            total = func(total, element)
            yield total

    def fin_max_len(s):
        P = manacher(s)
        intervals = [[(i-2)//2-P[i]//2, (i-2)//2+P[i]//2] for i in xrange(2,len(P)-2, 2)]
        dp = [0]*len(s)
        for l, r in reversed(intervals): 
            dp[r] = r-l+1
        for i in reversed(xrange(len(s)-1)):
            dp[i] = max(dp[i], dp[i+1]-2)
        return list(accumulate(dp, max, 0))
    
    l1, l2 = fin_max_len(s), fin_max_len(s[::-1])[::-1]
    return max(x*y for x, y in itertools.izip(l1, l2))


