def test_post_broken_body():
    response = client.post("/items/", data={"name": "Foo", "price": 50.5})
    assert response.status_code == 422, response.text
    assert response.json() == {
        "detail": [
            {
                "ctx": {
                    "colno": 1,
                    "doc": "name=Foo&price=50.5",
                    "lineno": 1,
                    "msg": "Expecting value",
                    "pos": 0,
                },
                "loc": ["body", 0],
                "msg": "Expecting value: line 1 column 1 (char 0)",
                "type": "value_error.jsondecode",
            }
        ]
    }
    with patch("json.loads", side_effect=Exception):
        response = client.post("/items/", json={"test": "test2"})
        assert response.status_code == 400, response.text
    assert response.json() == {"detail": "There was an error parsing the body"}

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


