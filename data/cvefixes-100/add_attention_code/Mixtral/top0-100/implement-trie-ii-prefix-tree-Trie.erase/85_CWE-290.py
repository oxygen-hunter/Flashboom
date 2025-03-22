def validate_agent_data(agent_data):
    if agent_data is None:
        return False, None

    # validate that the allowlist is proper JSON
    lists = json.loads(agent_data['allowlist'])

    # Validate exlude list contains valid regular expressions
    is_valid, _, err_msg = config.valid_exclude_list(lists.get('exclude'))
    if not is_valid:
        err_msg += " Exclude list regex is misformatted. Please correct the issue and try again."

    return is_valid, err_msg

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


