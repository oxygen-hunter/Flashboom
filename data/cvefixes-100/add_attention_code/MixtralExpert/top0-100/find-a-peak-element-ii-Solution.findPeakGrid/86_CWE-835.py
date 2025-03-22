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

def findPeakGrid(self, mat):
    """
    :type mat: List[List[int]]
    :rtype: List[int]
    """
    def get_vec(mat, i):
        return mat[i] if len(mat) > len(mat[0]) else (mat[j][i] for j in xrange(len(mat)))

    def check(mat, x):
        return max(get_vec(mat, x)) > max(get_vec(mat, x+1))

    left, right = 0, (max(len(mat), len(mat[0]))-1)-1
    while left <= right:
        mid = left + (right-left)//2
        if check(mat, mid):
            right = mid-1
        else:
            left = mid+1
    mav_val = max(get_vec(mat, left))
    result = [left, next(i for i, x in enumerate(get_vec(mat, left)) if x == mav_val)]
    return result if len(mat) > len(mat[0]) else result[::-1]


