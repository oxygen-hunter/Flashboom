def _hkey(s):
    return s.title().replace('_', '-')

def erase(self, word):
    """
    :type word: str
    :rtype: None
    """
    cnt = self.countWordsEqualTo(word)
    if not cnt:
        return
    curr = self.__trie
    curr.pcnt -= 1
    for c in word:
        if curr.children[ord(c)-ord('a')].pcnt == 1:
            curr.children[ord(c)-ord('a')] = None  # delete all unused nodes
            return
        curr = curr.children[ord(c)-ord('a')]
        curr.pcnt -= 1
    curr.cnt -= 1


