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

def equalizeWater(self, buckets, loss):
    """
    :type buckets: List[int]
    :type loss: int
    :rtype: float
    """
    def check(buckets, rate, x):
        return sum(b-x for b in buckets if b-x > 0)*rate >= sum(x-b for b in buckets if x-b > 0)

    EPS = 1e-5
    rate = (100-loss)/100.0
    left, right = float(min(buckets)), float(sum(buckets))/len(buckets)
    while right-left > EPS:
        mid = left + (right-left)/2
        if not check(buckets, rate, mid):
            right = mid
        else:
            left = mid
    return left


