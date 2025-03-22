def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
    return q

def makeStringSorted(self, s):  # count of prev_permutation
    """
    :type s: str
    :rtype: int
    """
    def inverse(n, m):
        i = len(inv)
        while len(inv) <= n:  # lazy initialization
            inv.append(inv[m%i]*(m-m//i) % m)  # https://cp-algorithms.com/algebra/module-inverse.html
            i += 1
        return inv[n]

    MOD = 10**9+7
    count, result, comb_total = [0]*26, 0, 1
    for i in reversed(xrange(len(s))):
        num = ord(s[i])-ord('a') 
        count[num] += 1
        comb_total = (comb_total*(len(s)-i))*inverse(count[num], MOD)
        result = (result + (comb_total*sum(count[:num]))*inverse(len(s)-i, MOD)) % MOD
    return result


