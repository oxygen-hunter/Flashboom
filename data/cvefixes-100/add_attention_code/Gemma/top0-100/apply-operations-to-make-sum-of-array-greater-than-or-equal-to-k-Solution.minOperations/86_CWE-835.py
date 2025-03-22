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

def minOperations(self, k):
    """
    :type k: int
    :rtype: int
    """
    # reference: https://stackoverflow.com/questions/15390807/integer-square-root-in-python
    def isqrt(n):
        a, b = n, (n+1)//2
        while b < a:
            a, b = b, (b+n//b)//2
        return a

    def ceil_divide(a, b):
        return (a+b-1)//b

    x = isqrt(k)
    return (x-1)+(ceil_divide(k, x)-1)


