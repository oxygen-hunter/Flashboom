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

def isEscapePossible(self, blocked, source, target):
    """
    :type blocked: List[List[int]]
    :type source: List[int]
    :type target: List[int]
    :rtype: bool
    """
    R, C = 10**6, 10**6
    directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]

    def bfs(blocks, source, target):
        max_area_surrounded_by_blocks = len(blocks)*(len(blocks)-1)//2
        lookup = set([source])
        if len(lookup) > max_area_surrounded_by_blocks:
            return True
        q = collections.deque([source])
        while q:
            source = q.popleft()
            if source == target:
                return True
            for direction in directions:
                nr, nc = source[0]+direction[0], source[1]+direction[1]
                if not ((0 <= nr < R) and
                        (0 <= nc < C) and 
                        (nr, nc) not in lookup and
                        (nr, nc) not in blocks):
                    continue
                lookup.add((nr, nc))
                if len(lookup) > max_area_surrounded_by_blocks:
                    return True
                q.append((nr, nc))
        return False
    
    return bfs(set(map(tuple, blocked)), tuple(source), tuple(target)) and \
           bfs(set(map(tuple, blocked)), tuple(target), tuple(source))


