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

def numberOfSets(self, n, k):
    """
    :type n: int
    :type k: int
    :rtype: int
    """
    MOD = 10**9+7
    def nCr(n, r):  # Time: O(n), Space: O(1)
        if n-r < r:
            return nCr(n, n-r)
        c = 1
        for k in xrange(1, r+1):
            c *= n-k+1
            c //= k
        return c
    
    # find k segments with 1+ length and (k+1) spaces with 0+ length s.t. total length is n-1
    # => find k segments with 0+ length and (k+1) spaces with 0+ length s.t. total length is n-k-1
    # => find the number of combinations of 2k+1 variables with total sum n-k-1
    # => H(2k+1, n-k-1)
    # => C((2k+1) + (n-k-1) - 1, n-k-1)
    # => C(n+k-1, n-k-1) = C(n+k-1, 2k)
    return nCr(n+k-1, 2*k) % MOD


