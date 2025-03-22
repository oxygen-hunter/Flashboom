def logout():
    if current_user is not None and current_user.is_authenticated:
        ub.delete_user_session(current_user.id, flask_session.get('_id',""))
        logout_user()
        if feature_support['oauth'] and (config.config_login_type == 2 or config.config_login_type == 3):
            logout_oauth_user()
    log.debug(u"User logged out")
    return redirect(url_for('web.login'))

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



