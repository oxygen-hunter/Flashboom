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

def isSolvable(self, words, result):
    """
    :type words: List[str]
    :type result: str
    :rtype: bool
    """
    def backtracking(words, result, i, j, carry, lookup, used):
        if j == len(result):
            return carry == 0

        if i != len(words):
            if j >= len(words[i]) or words[i][j] in lookup:
                return backtracking(words, result, i+1, j, carry, lookup, used)     
            for val in xrange(10):
                if val in used or (val == 0 and j == len(words[i])-1):
                    continue
                lookup[words[i][j]] = val
                used.add(val)
                if backtracking(words, result, i+1, j, carry, lookup, used):
                    return True
                used.remove(val)
                del lookup[words[i][j]]
            return False

        carry, val = divmod(carry + sum(lookup[w[j]] for w in words if j < len(w)), 10)
        if result[j] in lookup:
            return val == lookup[result[j]] and \
                   backtracking(words, result, 0, j+1, carry, lookup, used)
        if val in used or (val == 0 and j == len(result)-1):
            return False
        lookup[result[j]] = val
        used.add(val)
        if backtracking(words, result, 0, j+1, carry, lookup, used):
            return True
        used.remove(val)
        del lookup[result[j]]
        return False
    
    return backtracking([w[::-1] for w in words], result[::-1], 0, 0, 0, {}, set())


