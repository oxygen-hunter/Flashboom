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

def secondMinimum(self, n, edges, time, change):
    """
    :type n: int
    :type edges: List[List[int]]
    :type time: int
    :type change: int
    :rtype: int
    """
    INF = float("inf")
    def bfs(adj, start):
        q = [start]
        dist = [INF]*len(adj)
        dist[start] = 0
        while q:
            new_q = []
            for u in q:
                for v in adj[u]:
                    if dist[v] != INF:
                        continue
                    dist[v] = dist[u]+1
                    new_q.append(v)
            q = new_q
        return dist

    def calc_time(time, change, dist):
        result = 0
        for _ in xrange(dist):
            if result//change%2:
                result = (result//change+1)*change
            result += time
        return result

    adj = [[] for _ in xrange(n)]
    for u, v in edges:
        adj[u-1].append(v-1)
        adj[v-1].append(u-1)
    dist_to_end, dist_to_start = bfs(adj, 0), bfs(adj, n-1)

    dist = dist_to_end[n-1]+2  # always exists
    for i in xrange(n):  # case of detour
        if dist_to_end[i]+dist_to_start[i] == dist_to_end[n-1]:
            continue
        dist = min(dist, dist_to_end[i]+dist_to_start[i])  # find second min
        if dist == dist_to_end[n-1]+1:
            break
    return calc_time(time, change, dist)


