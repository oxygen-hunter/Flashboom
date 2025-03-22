def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
    return q

def getWinner(self, arr, k):
    """
    :type arr: List[int]
    :type k: int
    :rtype: int
    """
    result = arr[0]
    count = 0
    for i in xrange(1, len(arr)):
        if arr[i] > result:
            result = arr[i]
            count = 0
        count += 1
        if (count == k):
            break
    return result


