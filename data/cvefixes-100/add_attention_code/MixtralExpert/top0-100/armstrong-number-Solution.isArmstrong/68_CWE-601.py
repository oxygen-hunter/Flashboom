def make_homeserver(self, reactor, clock):
    hs = self.setup_test_homeserver("server", http_client=None)
    self.store = hs.get_datastore()
    return hs

def isArmstrong(self, N):
    """
    :type N: int
    :rtype: bool
    """
    n_str = str(N)
    return sum(int(i)**len(n_str) for i in n_str) == N


