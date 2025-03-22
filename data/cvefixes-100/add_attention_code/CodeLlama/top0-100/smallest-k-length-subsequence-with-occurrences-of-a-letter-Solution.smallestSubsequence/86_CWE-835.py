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

def smallestSubsequence(self, s, k, letter, repetition):
    """
    :type s: str
    :type k: int
    :type letter: str
    :type repetition: int
    :rtype: str
    """
    stk = []
    suffix = [0]*(len(s)+1)
    for i in reversed(xrange(len(suffix)-1)):
        suffix[i] = suffix[i+1]+(s[i] == letter)
    for i, c in enumerate(s): 
        while stk and stk[-1] > c and len(stk)+(len(s)-i) > k and (stk[-1] != letter or repetition+1 <= suffix[i]):
            repetition += (stk.pop() == letter)
        if len(stk) < min(k-(repetition-(c == letter)), k):
            repetition -= (c == letter)
            stk.append(c)
    return "".join(stk)


