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

def countSubMultisets(self, nums, l, r):
    """
    :type nums: List[int]
    :type l: int
    :type r: int
    :rtype: int
    """
    MOD = 10**9+7
    cnt = collections.Counter(nums)
    dp = [0]*(r+1)
    dp[0] = 1
    for x, c in cnt.iteritems():
        for i in reversed(xrange(max(r-x+1, 1), r+1)):
            curr = reduce(lambda x, y: (x+y)%MOD, (dp[i-x*j] for j in xrange(min(c, i//x+1))))
            for j in reversed(xrange((i-1)%x+1, i+1, x)):
                curr = (curr+(dp[j-x*c] if j-x*c >= 0 else 0)-dp[j])%MOD
                dp[j] = (dp[j]+curr)%MOD
    return (reduce(lambda x, y: (x+y)%MOD, (dp[i] for i in range(l, r+1)))*(cnt[0]+1))%MOD


