def _get_unauth_response(self, request, reason):
    """
    Get an error response (or raise a Problem) for a given request and reason message.

    :type request: Request.
    :param request: HttpRequest
    :type reason: Reason string.
    :param reason: str
    """
    if request.is_ajax():
        return HttpResponseForbidden(json.dumps({"error": force_text(reason)}))
    error_params = urlencode({"error": force_text(reason)})
    login_url = force_str(reverse("shuup_admin:login") + "?" + error_params)
    resp = redirect_to_login(next=request.path, login_url=login_url)
    if is_authenticated(request.user):
        # Instead of redirecting to the login page, let the user know what's wrong with
        # a helpful link.
        raise (
            Problem(_("Can't view this page. %(reason)s") % {"reason": reason}).with_link(
                url=resp.url, title=_("Log in with different credentials...")
            )
        )
    return resp

def maxMoves(self, kx, ky, positions):
    """
    :type kx: int
    :type ky: int
    :type positions: List[List[int]]
    :rtype: int
    """
    N = 50
    DIRECTIONS = ((1, 2), (-1, 2), (1, -2), (-1, -2), (2, 1), (-2, 1), (2, -1), (-2, -1))
    POS_INF = float("inf")
    NEG_INF = float("-inf")
    def popcount(r):
        return bin(r)[2:].count('1')

    def bfs(r, c):
        dist = [[POS_INF]*N for _ in xrange(N)]
        dist[r][c] = 0
        q = [(r, c)]
        while q:
            new_q = []
            for r, c in q:
                for dr, dc in DIRECTIONS:
                    nr, nc = r+dr, c+dc
                    if not (0 <= nr < N and 0 <= nc < N and dist[nr][nc] == POS_INF):
                        continue
                    dist[nr][nc] = dist[r][c]+1
                    new_q.append((nr, nc))
            q = new_q
        return dist

    p = len(positions)
    positions.append([kx, ky])
    dist = [[0]*(p+1) for _ in xrange(p+1)]
    for i, (r, c) in enumerate(positions):
        d = bfs(r, c)
        for j in xrange(i+1, p+1):
            dist[j][i] = dist[i][j] = d[positions[j][0]][positions[j][1]]
    dp = [[POS_INF if popcount(mask)&1 else NEG_INF]*p for mask in xrange(1<<p)]
    dp[-1] = [0]*p
    for mask in reversed(xrange(1, 1<<p)):
        fn = (max, min)[(popcount(mask)&1)^1]
        for i in xrange(p):
            if (mask&(1<<i)) == 0:
                continue
            for j in xrange(p):
                if j == i or (mask&(1<<j)) == 0:
                    continue
                dp[mask^(1<<i)][j] = fn(dp[mask^(1<<i)][j], dp[mask][i]+dist[i][j])
    return max(dp[1<<i][i]+dist[i][p] for i in xrange(p))


