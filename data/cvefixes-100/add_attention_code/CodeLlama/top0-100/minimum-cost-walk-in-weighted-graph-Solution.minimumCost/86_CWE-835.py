def data_received(self, data):
    self._buffer += data
    # try to parse the incoming data
    while self._buffer:
        try:
            buf = Buffer(self._buffer)
            try:
                header = header_from_binary(buf)
            except NotEnoughData:
                logger.debug('Not enough data while parsing header from client, waiting for more')
                return
            if len(buf) < header.body_size:
                logger.debug('We did not receive enough data from client. Need %s got %s', header.body_size,
                             len(buf))
                return
            # we have a complete message
            self.messages.put_nowait((header, buf))
            self._buffer = self._buffer[(header.header_size + header.body_size):]
        except Exception:
            logger.exception('Exception raised while parsing message from client')
            return

def minimumCost(self, n, edges, query):
    """
    :type n: int
    :type edges: List[List[int]]
    :type query: List[List[int]]
    :rtype: List[int]
    """
    class UnionFind(object):  # Time: O(n * alpha(n)), Space: O(n)
        def __init__(self, n):
            self.set = list(range(n))
            self.rank = [0]*n
            self.w = [-1]*n  # added

        def find_set(self, x):
            stk = []
            while self.set[x] != x:  # path compression
                stk.append(x)
                x = self.set[x]
            while stk:
                self.set[stk.pop()] = x
            return x

        def union_set(self, x, y, w):  # modified
            x, y = self.find_set(x), self.find_set(y)
            if x == y:
                self.w[x] &= w  # added
                return False
            if self.rank[x] > self.rank[y]:  # union by rank
                x, y = y, x
            self.set[x] = self.set[y]
            if self.rank[x] == self.rank[y]:
                self.rank[y] += 1
            self.w[y] &= self.w[x]&w  # added
            return True
        
        def cost(self, x):  # added
            return self.w[self.find_set(x)]

    uf = UnionFind(n)
    for u, v, w in edges:
        uf.union_set(u, v, w)
    result = [-1]*(len(query))
    for i, (s, t) in enumerate(query):
        if uf.find_set(s) != uf.find_set(t):
            continue
        result[i] = uf.cost(s) if s != t else 0
    return result


