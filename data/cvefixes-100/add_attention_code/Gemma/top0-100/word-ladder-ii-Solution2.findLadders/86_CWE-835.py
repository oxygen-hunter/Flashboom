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

def findLadders(self, beginWord, endWord, wordList):
    """
    :type beginWord: str
    :type endWord: str
    :type wordList: List[str]
    :rtype: List[List[str]]
    """
    dictionary = set(wordList)
    result, cur, visited, found, trace = [], [beginWord], set([beginWord]), False, defaultdict(list)

    while cur and not found:
        for word in cur:
            visited.add(word)

        next = set()
        for word in cur:
            for i in xrange(len(word)):
                for c in ascii_lowercase:
                    candidate = word[:i] + c + word[i + 1:]
                    if candidate not in visited and candidate in dictionary:
                        if candidate == endWord:
                            found = True
                        next.add(candidate)
                        trace[candidate].append(word)
        cur = next

    if found:
        self.backtrack(result, trace, [], endWord)

    return result



