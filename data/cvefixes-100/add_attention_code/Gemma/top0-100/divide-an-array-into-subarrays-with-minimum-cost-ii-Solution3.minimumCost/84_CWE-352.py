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

def minimumCost(self, nums, k, dist):
    """
    :type nums: List[int]
    :type k: int
    :type dist: int
    :rtype: int
    """
    sl1, sl2 = SortedList(), SortedList()
    mn, curr = float("inf"), 0
    for i in xrange(1, len(nums)):
        sl1.add(nums[i])
        curr += nums[i]
        if len(sl1) > k-1:
            curr -= sl1[-1]
            sl2.add(sl1.pop())
        if len(sl1)+len(sl2) > 1+dist:
            if sl2[0] <= nums[i-(1+dist)]:
                sl2.remove(nums[i-(1+dist)])
            else:
                sl1.remove(nums[i-(1+dist)])
                curr -= nums[i-(1+dist)]-sl2[0]
                sl1.add(sl2.pop(0))
        if len(sl1) == k-1:
            mn = min(mn, curr)
    return nums[0]+mn



