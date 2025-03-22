def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
    return q

def subStrHash(self, s, power, modulo, k, hashValue):
    """
    :type s: str
    :type power: int
    :type modulo: int
    :type k: int
    :type hashValue: int
    :rtype: str
    """
    h, idx = 0, -1
    pw = pow(power, k-1, modulo)
    for i in reversed(xrange(len(s))):
        if i+k < len(s):
            h = (h-(ord(s[i+k])-ord('a')+1)*pw)%modulo
        h = (h*power+(ord(s[i])-ord('a')+1))%modulo
        if h == hashValue:
            idx = i
    return s[idx:idx+k]


