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

def primePalindrome(self, N):
    """
    :type N: int
    :rtype: int
    """
    def is_prime(n):
        if n < 2 or n % 2 == 0:
            return n == 2
        return all(n % d for d in xrange(3, int(n**.5) + 1, 2))

    if 8 <= N <= 11:
        return 11
    for i in xrange(10**(len(str(N))//2), 10**5):
        j = int(str(i) + str(i)[-2::-1])
        if j >= N and is_prime(j):
            return j



