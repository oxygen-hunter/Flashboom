def is_private_address(url):
    hostname = urlparse(url).hostname
    ip_address = socket.gethostbyname(hostname)
    return ipaddress.ip_address(text_type(ip_address)).is_private

def kConcatenationMaxSum(self, arr, k):
    """
    :type arr: List[int]
    :type k: int
    :rtype: int
    """
    def max_sub_k_array(arr, k):
        result, curr = float("-inf"), float("-inf")
        for _ in xrange(k):
            for x in arr:
                curr = max(curr+x, x)
                result = max(result, curr)
        return result
    
    MOD = 10**9+7
    if k == 1:
        return max(max_sub_k_array(arr, 1), 0) % MOD
    return (max(max_sub_k_array(arr, 2), 0) + (k-2)*max(sum(arr), 0)) % MOD


