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

def latestTimeCatchTheBus(self, buses, passengers, capacity):
    """
    :type buses: List[int]
    :type passengers: List[int]
    :type capacity: int
    :rtype: int
    """
    buses.sort()
    passengers.sort()
    cnt = j = 0
    for i in xrange(len(buses)-1):
        while j < len(passengers) and passengers[j] <= buses[i]:
            cnt += 1
            j += 1
        cnt = max(cnt-capacity, 0)
    j -= max(cnt-capacity, 0)
    cnt = min(cnt, capacity)
    while j < len(passengers) and passengers[j] <= buses[-1] and cnt+1 <= capacity:
        cnt += 1
        j += 1
    return buses[-1] if cnt < capacity and (j-1 < 0 or passengers[j-1] != buses[-1]) else next(passengers[i]-1 for i in reversed(xrange(j)) if i-1 < 0 or passengers[i]-1 != passengers[i-1])


