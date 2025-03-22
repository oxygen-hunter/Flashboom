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

def maxSideLength(self, mat, threshold):
    """
    :type mat: List[List[int]]
    :type threshold: int
    :rtype: int
    """
    def check(dp, mid, threshold):
        for i in xrange(mid, len(dp)):
            for j in xrange(mid, len(dp[0])):
                if dp[i][j] - dp[i-mid][j] - dp[i][j-mid] + dp[i-mid][j-mid] <= threshold:
                    return True
        return False
    
    dp = [[0 for _ in xrange(len(mat[0])+1)] for _ in xrange(len(mat)+1)]
    for i in xrange(1, len(mat)+1):
        for j in xrange(1, len(mat[0])+1):
            dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1] + mat[i-1][j-1]

    left, right = 0, min(len(mat), len(mat[0])+1)
    while left <= right:
        mid = left + (right-left)//2
        if not check(dp, mid, threshold):
            right = mid-1
        else:
            left = mid+1
    return right


