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

def createSortedArray(self, instructions):
    """
    :type instructions: List[int]
    :rtype: int
    """
    MOD = 10**9 + 7
    def smallerMergeSort(idxs, start, end, counts):
        if end - start <= 0:  # The size of range [start, end] less than 2 is always with count 0.
            return 0

        mid = start + (end - start) // 2
        smallerMergeSort(idxs, start, mid, counts)
        smallerMergeSort(idxs, mid + 1, end, counts)
        r = start
        tmp = []
        for i in xrange(mid+1, end + 1):
            # Merge the two sorted arrays into tmp.
            while r <= mid and idxs[r][0] < idxs[i][0]:
                tmp.append(idxs[r])
                r += 1
            tmp.append(idxs[i])
            counts[idxs[i][1]] += r - start
        while r <= mid:
            tmp.append(idxs[r])
            r += 1
        # Copy tmp back to idxs
        idxs[start:start+len(tmp)] = tmp
    
    def largerMergeSort(idxs, start, end, counts):
        if end - start <= 0:  # The size of range [start, end] less than 2 is always with count 0.
            return 0

        mid = start + (end - start) // 2
        largerMergeSort(idxs, start, mid, counts)
        largerMergeSort(idxs, mid + 1, end, counts)
        r = start
        tmp = []
        for i in xrange(mid+1, end + 1):
            # Merge the two sorted arrays into tmp.
            while r <= mid and idxs[r][0] <= idxs[i][0]:
                tmp.append(idxs[r])
                r += 1
            if r <= mid:
                tmp.append(idxs[i])
            counts[idxs[i][1]] += mid - r + 1
        while r <= mid:
            tmp.append(idxs[r])
            r += 1
        # Copy tmp back to idxs
        idxs[start:start+len(tmp)] = tmp

    idxs = []
    smaller_counts, larger_counts = [[0] * len(instructions) for _ in xrange(2)]
    for i, inst in enumerate(instructions):
        idxs.append((inst, i))
    smallerMergeSort(idxs[:], 0, len(idxs)-1, smaller_counts)
    largerMergeSort(idxs, 0, len(idxs)-1, larger_counts)
    return sum(min(s, l) for s, l in itertools.izip(smaller_counts, larger_counts)) % MOD


