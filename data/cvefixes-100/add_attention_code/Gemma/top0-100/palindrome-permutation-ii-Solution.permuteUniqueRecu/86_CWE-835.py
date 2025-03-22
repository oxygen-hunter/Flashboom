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

def permuteUniqueRecu(self, mid, result, used, cur, nums):
    if len(cur) == len(nums):
        half_palindrome = ''.join(cur)
        result.append(half_palindrome + mid + half_palindrome[::-1])
        return
    for i in xrange(len(nums)):
        if not used[i] and not (i > 0 and nums[i-1] == nums[i] and used[i-1]):
            used[i] = True
            cur.append(nums[i])
            self.permuteUniqueRecu(mid, result, used, cur, nums)
            cur.pop()
            used[i] = False



