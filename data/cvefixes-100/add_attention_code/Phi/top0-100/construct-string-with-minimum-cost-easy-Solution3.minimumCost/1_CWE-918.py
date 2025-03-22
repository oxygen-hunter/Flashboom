def get_response(self, url, auth=None, http_method="get", **kwargs):
    if is_private_address(url) and settings.ENFORCE_PRIVATE_ADDRESS_BLOCK:
        raise Exception("Can't query private addresses.")

    # Get authentication values if not given
    if auth is None:
        auth = self.get_auth()

    # Then call requests to get the response from the given endpoint
    # URL optionally, with the additional requests parameters.
    error = None
    response = None
    try:
        response = requests_session.request(http_method, url, auth=auth, **kwargs)
        # Raise a requests HTTP exception with the appropriate reason
        # for 4xx and 5xx response status codes which is later caught
        # and passed back.
        response.raise_for_status()

        # Any other responses (e.g. 2xx and 3xx):
        if response.status_code != 200:
            error = "{} ({}).".format(self.response_error, response.status_code)

    except requests.HTTPError as exc:
        logger.exception(exc)
        error = "Failed to execute query. " "Return Code: {} Reason: {}".format(
            response.status_code, response.text
        )
    except requests.RequestException as exc:
        # Catch all other requests exceptions and return the error.
        logger.exception(exc)
        error = str(exc)

    # Return response and error.
    return response, error

def minimumCost(self, target, words, costs):
    """
    :type target: str
    :type words: List[str]
    :type costs: List[int]
    :rtype: int
    """
    INF = float("inf")
    class Trie(object):
        def __init__(self):
            self.__nodes = []
            self.__mns = []
            self.__new_node()
        
        def __new_node(self):
            self.__nodes.append([-1]*26)
            self.__mns.append(INF)
            return len(self.__nodes)-1

        def add(self, w, c):
            curr = 0
            for x in w:
                x = ord(x)-ord('a')
                if self.__nodes[curr][x] == -1:
                    self.__nodes[curr][x] = self.__new_node()
                curr = self.__nodes[curr][x]
            self.__mns[curr] = min(self.__mns[curr], c)
        
        def query(self, i):
            curr = 0
            for j in xrange(i, len(target)):
                x = ord(target[j])-ord('a')
                if self.__nodes[curr][x] == -1:
                    break
                curr = self.__nodes[curr][x]
                if self.__mns[curr] != INF:
                    dp[j+1] = min(dp[j+1], dp[i]+self.__mns[curr])

    trie = Trie()
    for w, c in itertools.izip(words, costs):
        trie.add(w, c)
    dp = [INF]*(len(target)+1)
    dp[0] = 0
    for i in xrange(len(target)):
        if dp[i] == INF:
            continue
        trie.query(i)
    return dp[-1] if dp[-1] != INF else -1


