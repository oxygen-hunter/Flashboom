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

def earliestAndLatest(self, n, firstPlayer, secondPlayer):
    """
    :type n: int
    :type firstPlayer: int
    :type secondPlayer: int
    :rtype: List[int]
    """
    def memoization(t, l, r, lookup):
        # t: total number of players,
        # l: number of players left to the nearest top2 player,
        # r: number of players right to the nearest top2 player
        if (t, l, r) not in lookup:
            if l == r:
                return (1, 1)
            if l > r:  # make sure l <= r
                l, r, = r, l
            result = [float("inf"), 0]
            for i in xrange(l+1):
                l_win_cnt, l_lose_cnt, nt, pair_cnt = i+1, l-i, (t+1)//2, t//2
                min_j = max(l_lose_cnt, r-(pair_cnt-l_lose_cnt))  # j >= l_lose_cnt and j >= r-(pair_cnt-l_lose_cnt)
                max_j = min(r-l_win_cnt, (nt-l_win_cnt)-1)  # j <= r-l_win_cnt and j <= (nt-l_win_cnt)-1
                for j in xrange(min_j, max_j+1):
                    tmp = memoization(nt, i, j, lookup)
                    result = min(result[0], tmp[0]+1), max(result[1], tmp[1]+1)
            lookup[t, l, r] = result
        return lookup[t, l, r]
    
    return memoization(n, firstPlayer-1, n-secondPlayer, {})


