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

def isValidPalindrome(self, s, k):
    """
    :type s: str
    :type k: int
    :rtype: bool
    """
    if s == s[::-1]:  # optional, to optimize special case
        return True

    dp = [[1] * len(s) for _ in xrange(2)]
    for i in reversed(xrange(len(s))):
        for j in xrange(i+1, len(s)):
            if s[i] == s[j]:
                dp[i%2][j] = 2 + dp[(i+1)%2][j-1] if i+1 <= j-1 else 2
            else:
                dp[i%2][j] = max(dp[(i+1)%2][j], dp[i%2][j-1])
    return len(s) <= k + dp[0][-1]


