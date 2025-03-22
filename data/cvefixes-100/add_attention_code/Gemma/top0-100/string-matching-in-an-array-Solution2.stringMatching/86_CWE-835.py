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

def stringMatching(self, words):
    """
    :type words: List[str]
    :rtype: List[str]
    """
    def getPrefix(pattern):
        prefix = [-1]*len(pattern)
        j = -1
        for i in xrange(1, len(pattern)):
            while j != -1 and pattern[j+1] != pattern[i]:
                j = prefix[j]
            if pattern[j+1] == pattern[i]:
                j += 1
            prefix[i] = j
        return prefix
        
    def kmp(text, pattern, prefix):
        if not pattern:
            return 0
        if len(text) < len(pattern):
            return -1
        j = -1
        for i in xrange(len(text)):
            while j != -1 and pattern[j+1] != text[i]:
                j = prefix[j]
            if pattern[j+1] == text[i]:
                j += 1
            if j+1 == len(pattern):
                return i-j
        return -1
        
    result = []
    for i, pattern in enumerate(words):
        prefix = getPrefix(pattern)
        for j, text in enumerate(words):
            if i != j and kmp(text, pattern, prefix) != -1:
                result.append(pattern)
                break
    return result



