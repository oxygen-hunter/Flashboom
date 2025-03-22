def add_security_headers(resp):
    resp.headers['Content-Security-Policy'] = "default-src 'self'" + ''.join([' '+host for host in config.config_trustedhosts.strip().split(',')]) + " 'unsafe-inline' 'unsafe-eval'; font-src 'self' data:; img-src 'self' data:"
    if request.endpoint == "editbook.edit_book" or config.config_use_google_drive:
        resp.headers['Content-Security-Policy'] += " *"
    elif request.endpoint == "web.read_book":
        resp.headers['Content-Security-Policy'] += " blob:;style-src-elem 'self' blob: 'unsafe-inline';"
    resp.headers['X-Content-Type-Options'] = 'nosniff'
    resp.headers['X-Frame-Options'] = 'SAMEORIGIN'
    resp.headers['X-XSS-Protection'] = '1; mode=block'
    resp.headers['Strict-Transport-Security'] = 'max-age=31536000;'
    return resp

def findIndices(self, nums, indexDifference, valueDifference):
    """
    :type nums: List[int]
    :type indexDifference: int
    :type valueDifference: int
    :rtype: List[int]
    """
    mx_i = mn_i = 0
    for i in xrange(len(nums)-indexDifference):
        if nums[i] > nums[mx_i]:
            mx_i = i
        elif nums[i] < nums[mn_i]:
            mn_i = i
        # we don't need to add abs for the difference since
        # - if nums[mx_i]-nums[i+indexDifference] < 0, then checking nums[i+indexDifference]-nums[mn_i] >= -(nums[mx_i]-nums[i+indexDifference]) > 0 can cover the case
        # - if nums[i+indexDifference]-nums[mn_i] < 0, then checking nums[mx_i]-nums[i+indexDifference] >= -(nums[i+indexDifference]-nums[mn_i]) > 0 can cover the case
        if nums[mx_i]-nums[i+indexDifference] >= valueDifference:
            return [mx_i, i+indexDifference]
        if nums[i+indexDifference]-nums[mn_i] >= valueDifference:
            return [mn_i, i+indexDifference]
    return [-1]*2


