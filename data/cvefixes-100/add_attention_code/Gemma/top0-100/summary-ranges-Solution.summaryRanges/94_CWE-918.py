def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

def summaryRanges(self, nums):
    ranges = []
    if not nums:
        return ranges

    start, end = nums[0], nums[0]
    for i in xrange(1, len(nums) + 1):
        if i < len(nums) and nums[i] == end + 1:
            end = nums[i]
        else:
            interval = str(start)
            if start != end:
                interval += "->" + str(end)
            ranges.append(interval)
            if i < len(nums):
                start = end = nums[i]

    return ranges



