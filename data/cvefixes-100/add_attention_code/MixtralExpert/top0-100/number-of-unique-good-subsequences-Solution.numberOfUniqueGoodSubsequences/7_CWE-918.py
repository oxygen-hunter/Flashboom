def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
    return q

def numberOfUniqueGoodSubsequences(self, binary):
    """
    :type binary: str
    :rtype: int
    """
    MOD = 10**9+7
    ends0, ends1 = 0, 0
    has_zero = False
    for b in binary:
        if b == '1':
            ends1 = (ends0+ends1+1)%MOD  # curr subsequences end with 1 is all prev distinct subsequences appended by 1 and plus "1"
        else:
            ends0 = (ends0+ends1)%MOD  # curr subsequences end with 0 is all prev distinct subsequences appended by 0 and don't plus "0"
            has_zero = True
    return (ends0+ends1+int(has_zero))%MOD  # add "0" if has_zero


