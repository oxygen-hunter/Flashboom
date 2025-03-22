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

def canMakeSquare(self, grid):
    """
    :type grid: List[List[str]]
    :rtype: bool
    """
    N, W = 3, 2
    return any(max(collections.Counter(grid[i+h][j+w] for h in xrange(W) for w in xrange(W)).itervalues()) >= W**2-1
               for i in xrange(N-W+1) for j in xrange(N-W+1))


