def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
    return q

def findSmallestInteger(self, nums, value):
    """
    :type nums: List[int]
    :type value: int
    :rtype: int
    """
    cnt = collections.Counter(x%value for x in nums)
    for i in xrange(len(nums)+1):
        if not cnt[i%value]:
            return i
        cnt[i%value] -= 1


