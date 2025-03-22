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


