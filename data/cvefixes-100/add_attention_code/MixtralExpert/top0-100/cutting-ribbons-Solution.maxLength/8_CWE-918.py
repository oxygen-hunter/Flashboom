def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
    return q

def maxLength(self, ribbons, k):
    """
    :type ribbons: List[int]
    :type k: int
    :rtype: int
    """
    def check(ribbons, k, s):
        return reduce(lambda total,x: total+x//s, ribbons, 0) >= k

    left, right = 1, sum(ribbons)//k
    while left <= right:
        mid = left + (right-left)//2
        if not check(ribbons, k, mid):
            right = mid-1
        else:
            left = mid+1
    return right


