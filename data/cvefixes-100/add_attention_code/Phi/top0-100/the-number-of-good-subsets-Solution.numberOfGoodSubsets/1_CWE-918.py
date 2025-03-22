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

def numberOfGoodSubsets(self, nums):
    """
    :type nums: List[int]
    :rtype: int
    """
    def sieve_of_eratosthenes(n):  # Time: O(n * log(logn)), Space: O(n)
        if n < 2:
            return []
        primes = [2]
        is_prime = [True]*((n+1)//2)
        for i in xrange(1, len(is_prime)):
            if not is_prime[i]:
                continue
            primes.append(2*i+1)
            for j in xrange(2*i*(i+1), len(is_prime), (2*i+1)):
                is_prime[j] = False
        return primes

    def to_mask(primes, x):
        mask, basis = 0, 1
        for p in primes:
            if x%p == 0:
                mask |= basis
            basis <<= 1
        return mask

    MOD = 10**9+7
    primes = sieve_of_eratosthenes(max(nums))
    dp = [0]*(1<<len(primes))  # dp[i] = the number of different good subsets of which the total product equals to the product of the primes in bitset i
    dp[0] = 1
    cnts = collections.Counter(nums)
    for x, cnt in cnts.iteritems():
        if x == 1 or any(x%(p*p) == 0 for p in primes if p*p <= x):
            continue
        mask = to_mask(primes, x)
        for i in xrange(len(dp)-1):
            if i&mask:
                continue
            dp[i|mask] = (dp[i|mask]+cnt*dp[i])%MOD
    return (pow(2, cnts[1], MOD))*(reduce(lambda total, x: (total+x)%MOD, dp, 0)-1)%MOD


