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

def countMatchingSubarrays(self, nums, pattern):
    """
    :type nums: List[int]
    :type pattern: List[int]
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

    def KMP(text, pattern):
        prefix = getPrefix(pattern)
        j = -1
        for i, x in enumerate(text):
            while j+1 > 0 and pattern[j+1] != x:
                j = prefix[j]
            if pattern[j+1] == x:
                j += 1
            if j+1 == len(pattern):
                yield i-j
                j = prefix[j]

    return sum(1 for _ in KMP((cmp(nums[i+1], nums[i]) for i in xrange(len(nums)-1)), pattern))


