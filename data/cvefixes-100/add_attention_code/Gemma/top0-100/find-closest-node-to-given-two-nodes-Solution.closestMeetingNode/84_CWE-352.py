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

def closestMeetingNode(self, edges, node1, node2):
    """
    :type edges: List[int]
    :type node1: int
    :type node2: int
    :rtype: int
    """
    def dfs(node):
        lookup = {}
        i = 0
        while node != -1:
            if node in lookup:
                break
            lookup[node] = i
            i += 1
            node = edges[node]
        return lookup
    
    lookup1, lookup2 = dfs(node1), dfs(node2)
    intersect = set(lookup1.iterkeys())&set(lookup2.iterkeys())
    return min(intersect, key=lambda x: (max(lookup1[x], lookup2[x]), x)) if intersect else -1


