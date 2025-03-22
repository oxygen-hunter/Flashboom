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


