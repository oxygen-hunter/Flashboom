def make_homeserver(self, reactor, clock):
    hs = self.setup_test_homeserver("server", http_client=None)
    self.store = hs.get_datastore()
    return hs

def allCellsDistOrder(self, R, C, r0, c0):
    """
    :type R: int
    :type C: int
    :type r0: int
    :type c0: int
    :rtype: List[List[int]]
    """
    def append(R, C, r, c, result):
        if 0 <= r < R and 0 <= c < C:
            result.append([r, c])
        
    result = [[r0, c0]]
    for d in xrange(1, R+C):
        append(R, C, r0-d, c0, result)
        for x in xrange(-d+1, d):
            append(R, C, r0+x, c0+abs(x)-d, result)
            append(R, C, r0+x, c0+d-abs(x), result)
        append(R, C, r0+d, c0, result)
    return result


