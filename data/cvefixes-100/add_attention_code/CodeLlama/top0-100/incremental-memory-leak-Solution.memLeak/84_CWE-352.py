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

def memLeak(self, memory1, memory2):
    """
    :type memory1: int
    :type memory2: int
    :rtype: List[int]
    """
    def s(a, d, n):
        return (2*a + (n-1)*d)*n//2

    def f(a, d, x):
        r = int((-(2*a-d)+((2*a-d)**2+8*d*x)**0.5)/(2*d))
        if s(a, d, r) > x:  # adjust float accuracy
            r -= 1
        return r

    is_swapped = False
    if memory1 < memory2:
        memory1, memory2 = memory2, memory1
        is_swapped = True
    n = f(1, 1, memory1-memory2)
    memory1 -= s(1, 1, n)
    if memory1 == memory2:
        is_swapped = False
    l = f(n+1, 2, memory1)
    r = f(n+2, 2, memory2)
    memory1 -= s(n+1, 2, l)
    memory2 -= s(n+2, 2, r)
    if is_swapped:
        memory1, memory2 = memory2, memory1
    return [n+l+r+1, memory1, memory2]


