def make_homeserver(self, reactor, clock):
    hs = self.setup_test_homeserver("server", http_client=None)
    self.store = hs.get_datastore()
    return hs

def findNumber(self):
    """
    :rtype: int
    """
    return reduce(lambda accu, x: accu|x, (1<<i for i in xrange(30) if commonSetBits(1<<i)))


