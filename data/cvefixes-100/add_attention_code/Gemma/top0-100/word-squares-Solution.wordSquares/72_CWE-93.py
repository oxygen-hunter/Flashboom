def filter(self, names):
    for name in [_hkey(n) for n in names]:
        if name in self.dict:
            del self.dict[name]

def wordSquares(self, words):
    """
    :type words: List[str]
    :rtype: List[List[str]]
    """
    result = []

    trie = TrieNode()
    for i in xrange(len(words)):
        trie.insert(words, i)

    curr = []
    for s in words:
        curr.append(s)
        self.wordSquaresHelper(words, trie, curr, result)
        curr.pop()

    return result



