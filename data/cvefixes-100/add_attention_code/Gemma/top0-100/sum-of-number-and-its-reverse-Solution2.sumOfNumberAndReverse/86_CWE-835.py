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

def sumOfNumberAndReverse(self, num):
    """
    :type num: int
    :rtype: bool
    """
    def reverse(n):
        result = 0
        while n:
            result = result*10 + n%10
            n //= 10            
        return result

    return any(x+reverse(x) == num for x in xrange(num//2, num+1))



