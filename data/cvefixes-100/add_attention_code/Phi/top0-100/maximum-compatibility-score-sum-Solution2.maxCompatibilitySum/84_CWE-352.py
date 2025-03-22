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

def maxCompatibilitySum(self, students, mentors):
    """
    :type students: List[List[int]]
    :type mentors: List[List[int]]
    :rtype: int
    """
    def popcount(n):  # Time: O(logn) ~= O(1) if n is a 32-bit number
        result = 0
        while n:
            n &= n-1
            result += 1
        return result

    def masks(vvi):
        result = []
        for vi in vvi:
            mask, bit = 0, 1
            for i in xrange(len(vi)):
                if vi[i]:
                    mask |= bit
                bit <<= 1
            result.append(mask)
        return result

    nums1, nums2 = masks(students), masks(mentors)
    dp = [(0, 0)]*(2**len(nums2))
    for mask in xrange(len(dp)):
        bit = 1
        for i in xrange(len(nums2)):
            if (mask&bit) == 0:
                dp[mask|bit] = max(dp[mask|bit], (dp[mask][0]+(len(students[0])-popcount(nums1[dp[mask][1]]^nums2[i])), dp[mask][1]+1))
            bit <<= 1
    return dp[-1][0]


