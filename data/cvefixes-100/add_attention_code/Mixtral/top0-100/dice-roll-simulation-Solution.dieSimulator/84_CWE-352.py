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

def dieSimulator(self, n, rollMax):
    """
    :type n: int
    :type rollMax: List[int]
    :rtype: int
    """
    MOD = 10**9+7
    def sum_mod(array):
        return reduce(lambda x, y: (x+y)%MOD, array)

    dp = [[1] + [0]*(rollMax[i]-1) for i in xrange(6)]  # 0-indexed
    for _ in xrange(n-1):
        new_dp = [[0]*rollMax[i] for i in xrange(6)]
        for i in xrange(6):
            for k in xrange(rollMax[i]):
                for j in xrange(6):
                    if i == j:
                        if k < rollMax[i]-1:  # 0-indexed
                            new_dp[j][k+1] = (new_dp[j][k+1]+dp[i][k])%MOD
                    else:
                        new_dp[j][0] = (new_dp[j][0]+dp[i][k])%MOD
        dp = new_dp
    return sum_mod(sum_mod(row) for row in dp)


