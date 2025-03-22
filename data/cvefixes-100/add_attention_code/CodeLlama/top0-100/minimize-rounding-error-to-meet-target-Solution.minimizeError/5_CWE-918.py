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

def minimizeError(self, prices, target):
    """
    :type prices: List[str]
    :type target: int
    :rtype: str
    """
    def kthElement(nums, k, compare=lambda a, b: a < b):
        def PartitionAroundPivot(left, right, pivot_idx, nums, compare):
            new_pivot_idx = left
            nums[pivot_idx], nums[right] = nums[right], nums[pivot_idx]
            for i in xrange(left, right):
                if compare(nums[i], nums[right]):
                    nums[i], nums[new_pivot_idx] = nums[new_pivot_idx], nums[i]
                    new_pivot_idx += 1

            nums[right], nums[new_pivot_idx] = nums[new_pivot_idx], nums[right]
            return new_pivot_idx

        left, right = 0, len(nums) - 1
        while left <= right:
            pivot_idx = random.randint(left, right)
            new_pivot_idx = PartitionAroundPivot(left, right, pivot_idx, nums, compare)
            if new_pivot_idx == k:
                return
            elif new_pivot_idx > k:
                right = new_pivot_idx - 1
            else:  # new_pivot_idx < k.
                left = new_pivot_idx + 1
    
    errors = []
    lower, upper = 0, 0
    for i, p in enumerate(map(float, prices)):
        lower += int(math.floor(p))
        upper += int(math.ceil(p))
        if p != math.floor(p):
            errors.append(p-math.floor(p))
    if not lower <= target <= upper:
        return "-1"

    lower_round_count = upper-target
    kthElement(errors, lower_round_count)
    result = 0.0
    for i in xrange(len(errors)):
        if i < lower_round_count:
            result += errors[i]
        else:
            result += 1.0-errors[i]
    return "{:.3f}".format(result)


