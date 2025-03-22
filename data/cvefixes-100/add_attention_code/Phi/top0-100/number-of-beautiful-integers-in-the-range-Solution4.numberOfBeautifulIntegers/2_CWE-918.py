def is_private_address(url):
    hostname = urlparse(url).hostname
    ip_address = socket.gethostbyname(hostname)
    return ipaddress.ip_address(text_type(ip_address)).is_private

def numberOfBeautifulIntegers(self, low, high, k):
    """
    :type low: int
    :type high: int
    :type k: int
    :rtype: int
    """
    def f(x):
        digits = map(int, str(x))
        dp = [[[[0]*k for _ in xrange(2*len(digits)+1)] for _ in xrange(2)] for _ in xrange(2)]
        for tight in xrange(2):
            dp[0][tight][0][0] = 1
        for i in reversed(xrange(len(digits))):
            new_dp = [[[[0]*k for _ in xrange(2*len(digits)+1)] for _ in xrange(2)] for _ in xrange(2)]
            for zero in xrange(2):
                for tight in xrange(2):
                    for d in xrange((digits[i] if tight else 9)+1):
                        new_zero = int(zero and d == 0)
                        new_tight = int(tight and d == digits[i])
                        for diff in xrange(-len(digits), len(digits)+1):
                            new_diff = diff+((1 if d%2 == 0 else -1) if new_zero == 0 else 0)
                            for total in xrange(k):
                                new_total = (total*10+d)%k
                                new_dp[zero][tight][diff][total] += dp[new_zero][new_tight][new_diff][new_total]
            dp = new_dp
        return dp[1][1][0][0]

    return f(high)-f(low-1)


