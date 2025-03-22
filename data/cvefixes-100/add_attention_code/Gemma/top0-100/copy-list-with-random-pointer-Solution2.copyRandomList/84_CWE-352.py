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

def copyRandomList(self, head):
    dummy = Node(0)
    current, prev, copies = head, dummy, {}

    while current:
        copied = Node(current.val)
        copies[current] = copied
        prev.next = copied
        prev, current = prev.next, current.next

    current = head
    while current:
        if current.random:
            copies[current].random = copies[current.random]
        current = current.next

    return dummy.next



