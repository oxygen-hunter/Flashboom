def _check_login_status(self, request: Request) -> LoginButton:
    # Each time the page is refreshed or loaded, check if the user is logged in and adapt label
    session = getattr(request, "session", None) or getattr(
        request.request, "session", None
    )
    if session is None or "oauth_info" not in session:
        return LoginButton(value=self.value, interactive=True)
    else:
        username = session["oauth_info"]["userinfo"]["preferred_username"]
        logout_text = self.logout_value.format(username)
        return LoginButton(logout_text, interactive=True)

def stringIndices(self, wordsContainer, wordsQuery):
    """
    :type wordsContainer: List[str]
    :type wordsQuery: List[str]
    :rtype: List[int]
    """
    INF = float("INF")
    class Trie(object):
        def __init__(self):
            self.__nodes = []
            self.__mns = []
            self.__new_node()
        
        def __new_node(self):
            self.__nodes.append([-1]*26)
            self.__mns.append((INF, INF))
            return len(self.__nodes)-1

        def add(self, i, w):
            curr = 0
            self.__mns[curr] = min(self.__mns[curr], (len(w), i))
            for c in reversed(w):
                x = ord(c)-ord('a')
                if self.__nodes[curr][x] == -1:
                    self.__nodes[curr][x] = self.__new_node()
                curr = self.__nodes[curr][x]
                self.__mns[curr] = min(self.__mns[curr], (len(w), i))
        
        def query(self, w):
            curr = 0
            for c in reversed(w):
                x = ord(c)-ord('a')
                if self.__nodes[curr][x] == -1:
                    break
                curr = self.__nodes[curr][x]
            return self.__mns[curr][1]

    trie = Trie()
    for i, w in enumerate(wordsContainer): 
        trie.add(i, w)
    return [trie.query(w) for w in wordsQuery]


