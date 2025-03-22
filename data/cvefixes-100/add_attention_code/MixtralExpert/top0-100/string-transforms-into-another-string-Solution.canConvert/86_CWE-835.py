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

def canConvert(self, str1, str2):
    """
    :type str1: str
    :type str2: str
    :rtype: bool
    """
    if str1 == str2:
        return True
    lookup = {}
    for i, j in itertools.izip(str1, str2):
        if lookup.setdefault(i, j) != j:
            return False
    return len(set(str2)) < 26


