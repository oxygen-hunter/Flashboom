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

def countStrobogrammaticUntil(self, num,  can_start_with_0):
    if can_start_with_0 and num in self.cache:
        return self.cache[num]

    count = 0
    if len(num) == 1:
        for c in ['0', '1', '8']:
            if num[0] >= c:
                count += 1
        self.cache[num] = count
        return count

    for key, val in self.lookup.iteritems():
        if can_start_with_0 or key != '0':
            if num[0] > key:
                if len(num) == 2:  # num is like "21"
                    count += 1
                else:  # num is like "201"
                    count += self.countStrobogrammaticUntil('9' * (len(num) - 2), True)
            elif num[0] == key:
                if len(num) == 2:  # num is like 12".
                    if num[-1] >= val:
                        count += 1
                else:
                    if num[-1] >= val:  # num is like "102".
                        count += self.countStrobogrammaticUntil(self.getMid(num), True)
                    elif (self.getMid(num) != '0' * (len(num) - 2)):  # num is like "110".
                        count += self.countStrobogrammaticUntil(self.getMid(num), True) - \
                                 self.isStrobogrammatic(self.getMid(num))

    if not can_start_with_0: # Sum up each length.
        for i in xrange(len(num) - 1, 0, -1):
            count += self.countStrobogrammaticByLength(i)
    else:
        self.cache[num] = count

    return count



