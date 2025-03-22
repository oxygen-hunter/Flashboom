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

def remainingMethods(self, n, k, invocations):
    """
    :type n: int
    :type k: int
    :type invocations: List[List[int]]
    :rtype: List[int]
    """
    def bfs():
        lookup = [False]*n
        lookup[k] = True
        q = [k]
        while q:
            new_q = []
            for u in q:
                for v in adj[u]:
                    if lookup[v]:
                        continue
                    lookup[v] = True
                    new_q.append(v)
            q = new_q
        return lookup

    adj = [[] for _ in xrange(n)]
    for u, v in invocations:
        adj[u].append(v)
    lookup = bfs()
    return [u for u in xrange(n) if not lookup[u]] if all(lookup[u] == lookup[v] for u, v in invocations) else range(n)


