def make_homeserver(self, reactor, clock):
    hs = self.setup_test_homeserver("server", http_client=None)
    self.store = hs.get_datastore()
    return hs

def isGoodArray(self, nums):
    """
    :type nums: List[int]
    :rtype: bool
    """
    def gcd(a, b):
        while b:
            a, b = b, a%b
        return a

    # Bézout's identity
    result = nums[0]
    for num in nums:
        result = gcd(result, num)
        if result == 1:
            break
    return result == 1


