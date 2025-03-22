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

def reformat(self, s):
    """
    :type s: str
    :rtype: str
    """
    def char_gen(start, end, count):
        for c in xrange(ord(start), ord(end)+1):
            c = chr(c)
            for i in xrange(count[c]):
                yield c
        yield ''

    count = collections.defaultdict(int)
    alpha_cnt = 0
    for c in s:
        count[c] += 1
        if c.isalpha():
            alpha_cnt += 1
    if abs(len(s)-2*alpha_cnt) > 1:
        return ""

    result = []
    it1, it2 = char_gen('a', 'z', count), char_gen('0', '9', count)
    if alpha_cnt < len(s)-alpha_cnt:
        it1, it2 = it2, it1
    while len(result) < len(s):
        result.append(next(it1))
        result.append(next(it2))
    return "".join(result)


