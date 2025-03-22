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

def maxSumSubmatrix(self, matrix, k):
    """
    :type matrix: List[List[int]]
    :type k: int
    :rtype: int
    """
    class BST(object):  # not avl, rbtree
        def __init__(self, val):
            self.val = val
            self.left = None
            self.right = None

        def insert(self, val):  # Time: O(h) = O(logn) ~ O(n)
            curr = self
            while curr:
                if curr.val >= val:
                    if curr.left:
                        curr = curr.left
                    else:
                        curr.left = BST(val)
                        return
                else:
                    if curr.right:
                        curr = curr.right
                    else:
                        curr.right = BST(val)
                        return

        def lower_bound(self, val):  # Time: O(h) = O(logn) ~ O(n)
            result, curr = None, self
            while curr:
                if curr.val >= val:
                    result, curr = curr, curr.left
                else:
                    curr = curr.right
            return result


    if not matrix:
        return 0

    m = min(len(matrix), len(matrix[0]))
    n = max(len(matrix), len(matrix[0]))
    result = float("-inf")

    for i in xrange(m):
        sums = [0] * n
        for j in xrange(i, m):
            for l in xrange(n):
                sums[l] += matrix[j][l] if m == len(matrix) else matrix[l][j]

            # Find the max subarray no more than K.
            accu_sum_set = BST(0)
            accu_sum = 0
            for sum in sums:
                accu_sum += sum
                node = accu_sum_set.lower_bound(accu_sum - k)
                if node:
                    result = max(result, accu_sum - node.val)
                accu_sum_set.insert(accu_sum)

    return result



