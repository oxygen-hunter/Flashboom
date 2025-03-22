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

def maxDiff(self, num):
    """
    :type num: int
    :rtype: int
    """
    digits = str(num)
    for b in digits:
        if b < '9':
            break
    if digits[0] != '1':
        a = digits[0]
    else:
        for a in digits:
            if a > '1':
                break
    return int(digits.replace(b, '9')) - \
           int(digits.replace(a, '1' if digits[0] != '1' else '0'))


