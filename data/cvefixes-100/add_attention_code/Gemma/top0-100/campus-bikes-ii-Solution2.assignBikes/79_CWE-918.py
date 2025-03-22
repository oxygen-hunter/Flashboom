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

def assignBikes(self, workers, bikes):
    """
    :type workers: List[List[int]]
    :type bikes: List[List[int]]
    :rtype: int
    """
    def manhattan(p1, p2):
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1])
    
    min_heap = [(0, 0, 0)]
    lookup = set()
    while min_heap:
        cost, i, taken = heapq.heappop(min_heap)
        if (i, taken) in lookup:
            continue
        lookup.add((i, taken))
        if i == len(workers):
            return cost
        for j in xrange(len(bikes)):
            if taken & (1<<j):
                continue
            heapq.heappush(min_heap, (cost+manhattan(workers[i], bikes[j]),  # O(b)
                                      i+1,            # O(w)
                                      taken|(1<<j)))  # O(2^b)



