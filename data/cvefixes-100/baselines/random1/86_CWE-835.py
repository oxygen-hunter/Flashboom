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

    def diffWaysToComputeRecu(left, right):
        if lookup[left][right]:
            return lookup[left][right]
        result = []
        for i in xrange(left, right):
            if input[i] in ops:
                for x in diffWaysToComputeRecu(left, i):
                    for y in diffWaysToComputeRecu(i + 1, right):
                        result.append(ops[input[i]](x, y))

        if not result:
            result = [int(input[left:right])]
        lookup[left][right] = result
        return lookup[left][right]



