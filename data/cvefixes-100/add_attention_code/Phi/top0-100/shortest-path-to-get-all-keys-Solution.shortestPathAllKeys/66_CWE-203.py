def create_transaction(
    payment: Payment,
    kind: str,
    payment_information: PaymentData,
    action_required: bool = False,
    gateway_response: GatewayResponse = None,
    error_msg=None,
) -> Transaction:
    """Create a transaction based on transaction kind and gateway response."""
    # Default values for token, amount, currency are only used in cases where
    # response from gateway was invalid or an exception occured
    if not gateway_response:
        gateway_response = GatewayResponse(
            kind=kind,
            action_required=False,
            transaction_id=payment_information.token,
            is_success=False,
            amount=payment_information.amount,
            currency=payment_information.currency,
            error=error_msg,
            raw_response={},
        )

    txn = Transaction.objects.create(
        payment=payment,
        action_required=action_required,
        kind=gateway_response.kind,
        token=gateway_response.transaction_id,
        is_success=gateway_response.is_success,
        amount=gateway_response.amount,
        currency=gateway_response.currency,
        error=gateway_response.error,
        customer_id=gateway_response.customer_id,
        gateway_response=gateway_response.raw_response or {},
        action_required_data=gateway_response.action_required_data or {},
    )
    return txn

def shortestPathAllKeys(self, grid):
    """
    :type grid: List[str]
    :rtype: int
    """
    directions = [(0, -1), (0, 1), (-1, 0), (1, 0)]

    def bfs(grid, source, locations):
        r, c = locations[source]
        lookup = [[False]*(len(grid[0])) for _ in xrange(len(grid))]
        lookup[r][c] = True
        q = collections.deque([(r, c, 0)])
        dist = {}
        while q:
            r, c, d = q.popleft()
            if source != grid[r][c] != '.':
                dist[grid[r][c]] = d
                continue
            for direction in directions:
                cr, cc = r+direction[0], c+direction[1]
                if not ((0 <= cr < len(grid)) and
                        (0 <= cc < len(grid[cr]))):
                    continue
                if grid[cr][cc] != '#' and not lookup[cr][cc]:
                    lookup[cr][cc] = True
                    q.append((cr, cc, d+1))
        return dist

    locations = {place: (r, c)
                 for r, row in enumerate(grid)
                 for c, place in enumerate(row)
                 if place not in '.#'}
    dists = {place: bfs(grid, place, locations) for place in locations}

    # Dijkstra's algorithm
    min_heap = [(0, '@', 0)]
    best = collections.defaultdict(lambda: collections.defaultdict(
                                               lambda: float("inf")))
    best['@'][0] = 0
    target_state = 2**sum(place.islower() for place in locations)-1
    while min_heap:
        cur_d, place, state = heapq.heappop(min_heap)
        if best[place][state] < cur_d:
            continue
        if state == target_state:
            return cur_d
        for dest, d in dists[place].iteritems():
            next_state = state
            if dest.islower():
                next_state |= (1 << (ord(dest)-ord('a')))
            elif dest.isupper():
                if not (state & (1 << (ord(dest)-ord('A')))):
                    continue
            if cur_d+d < best[dest][next_state]:
                best[dest][next_state] = cur_d+d
                heapq.heappush(min_heap, (cur_d+d, dest, next_state))
    return -1



