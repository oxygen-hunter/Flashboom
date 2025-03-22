def _check_login_status(self, request: Request) -> LoginButton:
    # Each time the page is refreshed or loaded, check if the user is logged in and adapt label
    session = getattr(request, "session", None) or getattr(
        request.request, "session", None
    )
    if session is None or "oauth_info" not in session:
        return LoginButton(value=self.value, interactive=True)
    else:
        username = session["oauth_info"]["userinfo"]["preferred_username"]
        logout_text = self.logout_value.format(username)
        return LoginButton(logout_text, interactive=True)

def getNumberOfBacklogOrders(self, orders):
    """
    :type orders: List[List[int]]
    :rtype: int
    """
    MOD = 10**9 + 7
    buy, sell  = [], []  # max_heap, min_heap
    for p, a, t in orders:
        if t == 0:
            heapq.heappush(buy, [-p, a])
        else:
            heapq.heappush(sell, [p, a])
        while sell and buy and sell[0][0] <= -buy[0][0]:
            k = min(buy[0][1], sell[0][1])
            tmp = heapq.heappop(buy)
            tmp[1] -= k
            if tmp[1]:
                heapq.heappush(buy, tmp)
            tmp = heapq.heappop(sell)
            tmp[1] -= k
            if tmp[1]:
                heapq.heappush(sell, tmp)
    return reduce(lambda x, y: (x+y) % MOD, (a for _, a in buy + sell))


