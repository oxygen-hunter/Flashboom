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

def maxCompatibilitySum(self, students, mentors):
    """
    :type students: List[List[int]]
    :type mentors: List[List[int]]
    :rtype: int
    """
    def popcount(n):  # Time: O(logn) ~= O(1) if n is a 32-bit number
        result = 0
        while n:
            n &= n-1
            result += 1
        return result

    def masks(vvi):
        result = []
        for vi in vvi:
            mask, bit = 0, 1
            for i in xrange(len(vi)):
                if vi[i]:
                    mask |= bit
                bit <<= 1
            result.append(mask)
        return result

    nums1, nums2 = masks(students), masks(mentors)
    dp = [(0, 0)]*(2**len(nums2))
    for mask in xrange(len(dp)):
        bit = 1
        for i in xrange(len(nums2)):
            if (mask&bit) == 0:
                dp[mask|bit] = max(dp[mask|bit], (dp[mask][0]+(len(students[0])-popcount(nums1[dp[mask][1]]^nums2[i])), dp[mask][1]+1))
            bit <<= 1
    return dp[-1][0]


