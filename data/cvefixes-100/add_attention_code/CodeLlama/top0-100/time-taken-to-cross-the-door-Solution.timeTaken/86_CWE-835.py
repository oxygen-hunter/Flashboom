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

def timeTaken(self, arrival, state):
    """
    :type arrival: List[int]
    :type state: List[int]
    :rtype: List[int]
    """
    def go_until(t):
        while curr[0] <= t and any(q):
            if not q[direction[0]]:
                direction[0] ^= 1
            result[q[direction[0]].popleft()] = curr[0]
            curr[0] += 1

    UNKNOWN, ENTERING, EXITING = range(-1, 1+1)
    result = [0]*len(arrival)
    curr, direction = [float("-inf")], [UNKNOWN]
    q = [collections.deque(), collections.deque()]
    for i, (a, s) in enumerate(itertools.izip(arrival, state)):
        go_until(a-1)
        q[s].append(i)
        if not (a <= curr[0]):
            curr, direction = [a], [EXITING]
    go_until(float("inf"))
    return result


