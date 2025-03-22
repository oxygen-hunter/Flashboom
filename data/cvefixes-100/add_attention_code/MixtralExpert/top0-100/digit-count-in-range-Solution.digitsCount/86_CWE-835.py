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

def digitsCount(self, d, low, high):
    """
    :type d: int
    :type low: int
    :type high: int
    :rtype: int
    """
    def digitsCount(n, k):
        pivot, result = 1, 0
        while n >= pivot:
            result += (n//(10*pivot))*pivot + \
                       min(pivot, max(n%(10*pivot) - k*pivot + 1, 0))
            if k == 0:
                result -= pivot
            pivot *= 10
        return result+1
    
    return digitsCount(high, d) - digitsCount(low-1, d)


