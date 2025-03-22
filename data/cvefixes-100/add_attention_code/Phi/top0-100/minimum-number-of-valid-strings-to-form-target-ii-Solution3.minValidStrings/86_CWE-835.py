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

def minValidStrings(self, words, target):
    """
    :type words: List[str]
    :type target: str
    :rtype: int
    """
    def getPrefix(pattern):
        prefix = [-1]*len(pattern)
        j = -1
        for i in xrange(1, len(pattern)):
            while j+1 > 0 and pattern[j+1] != pattern[i]:
                j = prefix[j]
            if pattern[j+1] == pattern[i]:
                j += 1
            prefix[i] = j
        return prefix

    def KMP(text, pattern, callback):
        prefix = getPrefix(pattern)
        j = -1
        for i in xrange(len(text)):
            while j+1 > 0 and pattern[j+1] != text[i]:
                j = prefix[j]
            if pattern[j+1] == text[i]:
                j += 1
            callback(i, j)
            if j+1 == len(pattern):
                j = prefix[j]

    def update(i, j):
        lookup[i] = max(lookup[i], j+1)

    lookup = [0]*len(target)
    for w in words:
        KMP(target, w, update)
    dp = [0]*(len(target)+1)
    for i in xrange(len(target)):
        if not lookup[i]:
            return -1
        dp[i+1] = dp[(i-lookup[i])+1]+1
    return dp[-1]


