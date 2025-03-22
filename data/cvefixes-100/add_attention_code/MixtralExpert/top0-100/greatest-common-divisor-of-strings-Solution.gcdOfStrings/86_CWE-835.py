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

def gcdOfStrings(self, str1, str2):
    """
    :type str1: str
    :type str2: str
    :rtype: str
    """
    def check(s, common):
        i = 0
        for c in s:
            if c != common[i]:
                return False
            i = (i+1)%len(common)
        return True

    def gcd(a, b):  # Time: O(log(min(a, b)))
        while b:
            a, b = b, a % b
        return a
    
    if not str1 or not str2:
        return ""
    c = gcd(len(str1), len(str2))
    result = str1[:c]
    return result if check(str1, result) and check(str2, result) else ""


