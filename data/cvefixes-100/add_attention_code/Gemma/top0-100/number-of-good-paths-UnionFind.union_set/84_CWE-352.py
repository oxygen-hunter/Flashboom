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

def union_set(self, x, y, v):  # modified
    x, y = self.find_set(x), self.find_set(y)
    if x == y:
        return 0  # modified
    if self.rank[x] > self.rank[y]:  # union by rank
        x, y = y, x
    self.set[x] = self.set[y]
    if self.rank[x] == self.rank[y]:
        self.rank[y] += 1
    cx, cy = self.cnt[x][v], self.cnt[y][v]  # added
    self.cnt[y] = collections.Counter({v:cx+cy})  # added
    return cx*cy  # modified



