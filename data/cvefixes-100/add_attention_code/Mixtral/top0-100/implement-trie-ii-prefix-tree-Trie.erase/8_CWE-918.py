def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
    return q

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


