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

def findAnswer(self, n, edges):
    """
    :type n: int
    :type edges: List[List[int]]
    :rtype: List[bool]
    """
    INF = float("inf")
    def dijkstra(start):
        best = [INF]*len(adj)
        best[start] = 0
        min_heap = [(0, start)]
        while min_heap:
            curr, u = heapq.heappop(min_heap)
            if curr > best[u]:
                continue
            for v, w in adj[u]:     
                if best[v] <= curr+w:
                    continue
                best[v] = curr+w
                heapq.heappush(min_heap, (best[v], v))
        return best

    adj = [[] for _ in xrange(n)]
    for u, v, w in edges:
        adj[u].append((v, w))
        adj[v].append((u, w))
    dist1 = dijkstra(0)
    dist2 = dijkstra(n-1)
    return [(dist1[u] != INF != dist2[v] and dist1[u]+w+dist2[v] == dist1[n-1]) or
            (dist2[u] != INF != dist1[v] and dist2[u]+w+dist1[v] == dist2[0])
            for i, (u, v, w) in enumerate(edges)]


