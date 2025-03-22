def get_response(self, url, auth=None, http_method="get", **kwargs):
    if is_private_address(url) and settings.ENFORCE_PRIVATE_ADDRESS_BLOCK:
        raise Exception("Can't query private addresses.")

    # Get authentication values if not given
    if auth is None:
        auth = self.get_auth()

    # Then call requests to get the response from the given endpoint
    # URL optionally, with the additional requests parameters.
    error = None
    response = None
    try:
        response = requests_session.request(http_method, url, auth=auth, **kwargs)
        # Raise a requests HTTP exception with the appropriate reason
        # for 4xx and 5xx response status codes which is later caught
        # and passed back.
        response.raise_for_status()

        # Any other responses (e.g. 2xx and 3xx):
        if response.status_code != 200:
            error = "{} ({}).".format(self.response_error, response.status_code)

    except requests.HTTPError as exc:
        logger.exception(exc)
        error = "Failed to execute query. " "Return Code: {} Reason: {}".format(
            response.status_code, response.text
        )
    except requests.RequestException as exc:
        # Catch all other requests exceptions and return the error.
        logger.exception(exc)
        error = str(exc)

    # Return response and error.
    return response, error

def searchRange(self, nums, target):
    """
    :type nums: List[int]
    :type target: int
    :rtype: List[int]
    """
    def binarySearch(n, check):  # usually use
        left, right = 0, n-1  # search in [0, n-1], return n if not found
        while left <= right:
            mid = left + (right-left)//2
            if check(mid):
                right = mid-1
            else:
                left = mid+1
        return left  # or return right+1

    def binarySearch2(n, check):  # frequently use
        left, right = 0, n  # search in [0, n), return n if not found
        while left < right:
            mid = left + (right-left)//2
            if check(mid):
                right = mid
            else:
                left = mid+1
        return left  # or return right

    def binarySearch3(n, check):  # never use
        left, right = -1, n-1  # search in (-1, n-1], return n if not found
        while left < right:
            mid = right - (right-left)//2
            if check(mid):
                right = mid-1
            else:
                left = mid
        return left+1  # or return right+1

    def binarySearch4(n, check):  # sometimes use
        left, right = -1, n  # search in (-1, n), return n if not found
        while right-left >= 2:
            mid = left + (right-left)//2
            if check(mid):
                right = mid
            else:
                left = mid
        return left+1  # or return right

    # Find the first idx where nums[idx] >= target
    left = binarySearch(len(nums), lambda i: nums[i] >= target)
    if left == len(nums) or nums[left] != target:
        return [-1, -1]
    # Find the first idx where nums[idx] > target
    right = binarySearch(len(nums), lambda i: nums[i] > target)
    return [left, right-1]


