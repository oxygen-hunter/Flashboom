def get_file(recipe):
    if not recipe.link:
        recipe.link = Dropbox.get_share_link(recipe)
        recipe.save()

    response = requests.get(recipe.link.replace('www.dropbox.', 'dl.dropboxusercontent.'))

    return io.BytesIO(response.content)

def findWords(self, board, words):
    """
    :type board: List[List[str]]
    :type words: List[str]
    :rtype: List[str]
    """
    visited = [[False for j in xrange(len(board[0]))] for i in xrange(len(board))]
    result = {}
    trie = TrieNode()
    for word in words:
        trie.insert(word)

    for i in xrange(len(board)):
        for j in xrange(len(board[0])):
            self.findWordsRecu(board, trie, 0, i, j, visited, [], result)

    return result.keys()



