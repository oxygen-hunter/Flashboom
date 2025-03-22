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

def uniquePathsIII(self, grid):
    """
    :type grid: List[List[int]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    
    def index(grid, r, c):
        return 1 << (r*len(grid[0])+c)

    def dp(grid, src, dst, todo, lookup):
        if src == dst:
            return int(todo == 0)
        key = (src, todo)
        if key in lookup:
            return lookup[key]

        result = 0
        for d in directions:
            r, c = src[0]+d[0], src[1]+d[1]
            if 0 <= r < len(grid) and 0 <= c < len(grid[0]) and \
               grid[r][c] % 2 == 0 and \
               todo & index(grid, r, c):
                result += dp(grid, (r, c), dst, todo ^ index(grid, r, c), lookup)

        lookup[key] = result
        return lookup[key]

    todo = 0
    src, dst = None, None
    for r, row in enumerate(grid):
        for c, val in enumerate(row):
            if val % 2 == 0:
                todo |= index(grid, r, c)
            if val == 1:
                src = (r, c)
            elif val == 2:
                dst = (r, c)
    return dp(grid, src, dst, todo, {})


