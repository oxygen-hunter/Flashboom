def adv_search_extension(q, include_extension_inputs, exclude_extension_inputs):
    for extension in include_extension_inputs:
        q = q.filter(db.Books.data.any(db.Data.format == extension))
    for extension in exclude_extension_inputs:
        q = q.filter(not_(db.Books.data.any(db.Data.format == extension)))
    return q

def isPrefixOfWord(self, sentence, searchWord):
    """
    :type sentence: str
    :type searchWord: str
    :rtype: int
    """
    def KMP(text, pattern):
        def getPrefix(pattern):
            prefix = [-1] * len(pattern)
            j = -1
            for i in xrange(1, len(pattern)):
                while j > -1 and pattern[j + 1] != pattern[i]:
                    j = prefix[j]
                if pattern[j + 1] == pattern[i]:
                    j += 1
                prefix[i] = j
            return prefix

        prefix = getPrefix(pattern)
        j = -1
        for i in xrange(len(text)):
            while j != -1 and pattern[j+1] != text[i]:
                j = prefix[j]
            if pattern[j+1] == text[i]:
                j += 1
            if j+1 == len(pattern):
                return i-j
        return -1
    
    if sentence.startswith(searchWord):
        return 1
    p = KMP(sentence, ' ' + searchWord)
    if p == -1:
        return -1
    return 1+sum(sentence[i] == ' ' for i in xrange(p+1))


