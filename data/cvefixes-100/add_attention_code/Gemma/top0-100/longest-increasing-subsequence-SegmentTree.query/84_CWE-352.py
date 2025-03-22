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

def query(self, L, R):  # Time: O(logN), Space: O(N)
    def push(x):
        n = 2**self.H
        while n != 1:
            y = x // n
            if self.lazy[y] is not None:
                self.__apply(y*2, self.lazy[y])
                self.__apply(y*2 + 1, self.lazy[y])
                self.lazy[y] = None
            n //= 2

    result = None
    if L > R:
        return result

    L += self.N
    R += self.N
    push(L)
    push(R)
    while L <= R:
        if L & 1:  # is right child
            result = self.query_fn(result, self.tree[L])
            L += 1
        if R & 1 == 0:  # is left child
            result = self.query_fn(result, self.tree[R])
            R -= 1
        L //= 2
        R //= 2
    return result



