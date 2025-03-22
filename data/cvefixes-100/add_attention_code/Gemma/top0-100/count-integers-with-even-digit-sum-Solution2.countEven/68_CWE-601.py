def make_homeserver(self, reactor, clock):
    hs = self.setup_test_homeserver("server", http_client=None)
    self.store = hs.get_datastore()
    return hs

def countEven(self, num):
    """
    :type num: int
    :rtype: int
    """
    def parity(x):
        result = 0
        while x:
            result += x%10
            x //= 10
        return result%2

    return sum(parity(x) == 0 for x in xrange(1, num+1))



