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

def countSubIslands(self, grid1, grid2):
    """
    :type grid1: List[List[int]]
    :type grid2: List[List[int]]
    :rtype: int
    """
    directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
    def dfs(grid1, grid2, i, j):
        if not (0 <= i < len(grid2) and
                0 <= j < len(grid2[0]) and
                grid2[i][j] == 1):
            return 1
        grid2[i][j] = 0
        result = grid1[i][j]
        for di, dj in directions:
            result &= dfs(grid1, grid2, i+di, j+dj)
        return result
        
    return sum(dfs(grid1, grid2, i, j) for i in xrange(len(grid2)) for j in xrange(len(grid2[0])) if grid2[i][j])


