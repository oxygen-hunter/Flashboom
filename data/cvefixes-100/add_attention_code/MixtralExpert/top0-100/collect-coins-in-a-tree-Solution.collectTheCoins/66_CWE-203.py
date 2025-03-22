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

def collectTheCoins(self, coins, edges):
    """
    :type coins: List[int]
    :type edges: List[List[int]]
    :rtype: int
    """
    DISTANCE = 2

    adj = [set() for _ in xrange(len(coins))]
    for u, v in edges:
        adj[u].add(v)
        adj[v].add(u)
    n = len(coins)
    q = []
    for u in xrange(len(coins)):
        while len(adj[u]) == 1 and not coins[u]:
            v = adj[u].pop()
            adj[v].remove(u)
            n -= 1
            u = v
    q = [u for u in xrange(len(coins)) if len(adj[u]) == 1]
    for _ in xrange(DISTANCE):
        new_q = []
        for u in q:
            if not adj[u]:
                assert(n == 1)
                break
            v = adj[u].pop()
            adj[v].remove(u)
            n -= 1
            if len(adj[v]) == 1:
                new_q.append(v)
        q = new_q
    return (n-1)*2


