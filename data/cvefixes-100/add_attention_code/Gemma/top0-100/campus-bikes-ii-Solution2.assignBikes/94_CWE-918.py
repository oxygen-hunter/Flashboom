def swaggerui_static(filename):
    return send_file(os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(__file__))), 'libs', 'flask_restx',
                     'static', filename))

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



