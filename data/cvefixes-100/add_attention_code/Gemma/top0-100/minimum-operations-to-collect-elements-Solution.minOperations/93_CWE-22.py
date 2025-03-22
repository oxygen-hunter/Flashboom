def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def minOperations(self, nums, k):
    """
    :type nums: List[int]
    :type k: int
    :rtype: int
    """
    lookup = [False]*k
    for i in reversed(xrange(len(nums))):
        if nums[i] > len(lookup) or lookup[nums[i]-1]:
            continue
        lookup[nums[i]-1] = True
        k -= 1
        if not k:
            break
    return len(nums)-i


