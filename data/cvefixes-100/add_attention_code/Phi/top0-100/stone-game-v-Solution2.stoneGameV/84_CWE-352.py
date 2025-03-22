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

def stoneGameV(self, stoneValue):
    """
    :type stoneValue: List[int]
    :rtype: int
    """
    n = len(stoneValue)
    prefix = [0]
    for v in stoneValue:
        prefix.append(prefix[-1] + v)

    mid = [[0]*n for _ in xrange(n)]
    for l in xrange(1, n+1):
        for i in xrange(n-l+1):
            j = i+l-1
            p = i if l == 1 else mid[i][j-1]
            while prefix[p]-prefix[i] < prefix[j+1]-prefix[p]:
                p += 1  # Time: O(n^2) in total
            mid[i][j] = p
    
    rmq = [[0]*n for _ in xrange(n)]
    for i in xrange(n):
        rmq[i][i] = stoneValue[i]

    dp = [[0]*n for _ in xrange(n)]
    for l in xrange(2, n+1):
        for i in xrange(n-l+1):
            j = i+l-1
            p = mid[i][j]
            max_score = 0
            if prefix[p]-prefix[i] == prefix[j+1]-prefix[p]:
                max_score = max(rmq[i][p-1], rmq[j][p])
            else:
                if i <= p-2:
                    max_score = max(max_score, rmq[i][p-2])
                if p <= j:
                    max_score = max(max_score, rmq[j][p])
            dp[i][j] = max_score
            rmq[i][j] = max(rmq[i][j-1], (prefix[j+1]-prefix[i]) + max_score)
            rmq[j][i] = max(rmq[j][i+1], (prefix[j+1]-prefix[i]) + max_score)
    return dp[0][n-1]


