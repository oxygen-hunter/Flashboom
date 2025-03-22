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

def dieSimulator(self, n, rollMax):
    """
    :type n: int
    :type rollMax: List[int]
    :rtype: int
    """
    MOD = 10**9+7
    def sum_mod(array):
        return reduce(lambda x, y: (x+y)%MOD, array)

    dp = [[1] + [0]*(rollMax[i]-1) for i in xrange(6)]  # 0-indexed
    for _ in xrange(n-1):
        new_dp = [[0]*rollMax[i] for i in xrange(6)]
        for i in xrange(6):
            for k in xrange(rollMax[i]):
                for j in xrange(6):
                    if i == j:
                        if k < rollMax[i]-1:  # 0-indexed
                            new_dp[j][k+1] = (new_dp[j][k+1]+dp[i][k])%MOD
                    else:
                        new_dp[j][0] = (new_dp[j][0]+dp[i][k])%MOD
        dp = new_dp
    return sum_mod(sum_mod(row) for row in dp)


