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

def numberOfWays(self, s, t, k):
    """
    :type s: str
    :type t: str
    :type k: int
    :rtype: int
    """
    MOD = 10**9+7
    def matrix_mult(A, B):
        ZB = zip(*B)
        return [[sum(a*b % MOD for a, b in itertools.izip(row, col)) % MOD for col in ZB] for row in A]
 
    def matrix_expo(A, K):
        result = [[int(i == j) for j in xrange(len(A))] for i in xrange(len(A))]
        while K:
            if K % 2:
                result = matrix_mult(result, A)
            A = matrix_mult(A, A)
            K /= 2
        return result

    # Template: https://cp-algorithms.com/string/z-function.html
    def z_function(s):  # Time: O(n), Space: O(n)
        z = [0]*len(s)
        l, r = 0, 0
        for i in xrange(1, len(z)):
            if i <= r:
                z[i] = min(r-i+1, z[i-l])
            while i+z[i] < len(z) and s[z[i]] == s[i+z[i]]:
                z[i] += 1
            if i+z[i]-1 > r:
                l, r = i, i+z[i]-1
        return z

    n = len(s)
    T = [[0, 1],
         [n-1, (n-1)-1]]
    dp = [1, 0]
    dp = matrix_mult([dp], matrix_expo(T, k))[0]  # [dp[0], dp[1]] * T^k
    z = z_function(t+s+s[:-1])
    return reduce(lambda a, b: (a+b)%MOD, (dp[int(i != 0)] for i in xrange(n) if z[i+len(t)] >= len(t)), 0)


